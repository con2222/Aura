

#include "Player/AuraPlayerState.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Net/UnrealNetwork.h"

void AAuraPlayerState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(AAuraPlayerState, Level);
	DOREPLIFETIME(AAuraPlayerState, XP);
	DOREPLIFETIME(AAuraPlayerState, AttributePoints);
	DOREPLIFETIME(AAuraPlayerState, SpellPoints);
}

AAuraPlayerState::AAuraPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>(TEXT("AttributeSet"));
	
	SetNetUpdateFrequency(100.f);
}

UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AAuraPlayerState::OnRep_Level(int32 OldLevel)
{
	OnLevelChangedDelegate.Broadcast(Level);
}

void AAuraPlayerState::OnRep_XP(int32 OldXP)
{
	OnXPChangedDelegate.Broadcast(XP);
}

void AAuraPlayerState::OnRep_AttributePoint(int32 OldAttributePoint)
{
	OnAttributePointChangedDelegate.Broadcast(AttributePoints);
}

void AAuraPlayerState::OnRep_SpellPoint(int32 OldSpellPoint)
{
	OnSpellPointChangedDelegate.Broadcast(SpellPoints);
}

void AAuraPlayerState::AddToAttributePoints(int32 Points)
{
	AttributePoints += Points;
	OnAttributePointChangedDelegate.Broadcast(AttributePoints);
}

void AAuraPlayerState::AddToSpellPoints(int32 Points)
{
	SpellPoints += Points;
	OnSpellPointChangedDelegate.Broadcast(SpellPoints);
}

void AAuraPlayerState::AddPlayerLevel(int32 NewLevel)
{
	Level += NewLevel;
	OnLevelChangedDelegate.Broadcast(Level);
}

void AAuraPlayerState::SetPlayerLevel(int32 NewLevel)
{
	Level = NewLevel;
	OnLevelChangedDelegate.Broadcast(Level);
}

void AAuraPlayerState::AddToXP(int32 NewXP)
{
	XP += NewXP;
	OnXPChangedDelegate.Broadcast(XP);
}

void AAuraPlayerState::SetXP(int32 NewXP)
{
	XP = NewXP;
	OnXPChangedDelegate.Broadcast(XP);
}
