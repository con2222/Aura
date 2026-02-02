


#include "Character/AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/AuraPlayerState.h"

AAuraCharacter::AAuraCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 400.0f, 0.0f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 1000.0f;
	
	CameraBoom = CreateDefaultSubobject<UCameraComponent>("CameraBoom");
	CameraBoom->SetupAttachment(SpringArm);
	
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	// For the server
	InitAbilityActorInfo();
	
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
	// For the client
	InitAbilityActorInfo();
}


void AAuraCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAuraCharacter::InitAbilityActorInfo()
{
	if (AAuraPlayerState* State = CastChecked<AAuraPlayerState>(GetPlayerState()))
	{
		AbilitySystemComponent = State->GetAbilitySystemComponent();
		AttributeSet = State->GetAttributeSet();
		State->GetAbilitySystemComponent()->InitAbilityActorInfo(GetPlayerState(), this);
	}
}

void AAuraCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
