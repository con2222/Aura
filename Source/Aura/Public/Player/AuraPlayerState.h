

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	AAuraPlayerState();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	class UAttributeSet* GetAttributeSet() const { return AttributeSet; }
	
private:
	UPROPERTY()
	TObjectPtr<class UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<class UAttributeSet> AttributeSet;
protected:
	
};
