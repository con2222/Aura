

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraBaseCharacter.h"
#include "AuraCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraBaseCharacter
{
	GENERATED_BODY()
	
public:
	AAuraCharacter();
	
	void PossessedBy(AController* NewController) override;
	void OnRep_PlayerState() override;
	
	virtual void Tick(float DeltaTime) override;
	
protected:
	
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm;
	
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* CameraBoom;
	
	void InitAbilityActorInfo();

};
