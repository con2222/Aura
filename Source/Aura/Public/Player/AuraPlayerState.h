

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerStatChanged, int32 /*StatValue*/)

/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	AAuraPlayerState();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	class UAttributeSet* GetAttributeSet() const { return AttributeSet; }
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class ULevelUpInfo> LevelUpInfo;
	
	FOnPlayerStatChanged OnXPChangedDelegate;
	FOnPlayerStatChanged OnLevelChangedDelegate;
	FOnPlayerStatChanged OnAttributePointChangedDelegate;
	FOnPlayerStatChanged OnSpellPointChangedDelegate;
	
protected:

    UPROPERTY(VisibleAnywhere)
    TObjectPtr<class UAbilitySystemComponent> AbilitySystemComponent;
    
    UPROPERTY()
    TObjectPtr<class UAttributeSet> AttributeSet;
	
private:
	
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_Level)
	int32 Level = 1;
	
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_XP)
	int32 XP = 1;
	
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_AttributePoint)
	int32 AttributePoints = 0;
	
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_SpellPoint)
	int32 SpellPoints = 0;

	UFUNCTION()
	void OnRep_Level(int32 OldLevel);
	
	UFUNCTION()
	void OnRep_XP(int32 OldXP);
	
	UFUNCTION()
	void OnRep_AttributePoint(int32 OldAttributePoint);
	
	UFUNCTION()
	void OnRep_SpellPoint(int32 OldSpellPoint);

public:
	
	FORCEINLINE int32 GetAttributePoints() const { return AttributePoints; }
	void AddToAttributePoints(int32 Points);
	
	FORCEINLINE int32 GetSpellPoints() const { return SpellPoints; }
	void AddToSpellPoints(int32 Points);
	
	
	FORCEINLINE int32 GetPlayerLevel() const { return Level; }
	void AddPlayerLevel(int32 NewLevel);
	void SetPlayerLevel(int32 NewLevel);
	
	FORCEINLINE int32 GetXP() const { return XP; }	
	void AddToXP(int32 NewXP);
	void SetXP(int32 NewXP);
};
