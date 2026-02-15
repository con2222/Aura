


#include "Input/AuraInputConfig.h"

const UInputAction* UAuraInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag,
	bool bLogNotFound) const
{
	for (const auto& AbilityInputAction : AbilityInputActions)
	{
		if (AbilityInputAction.InputAction && InputTag.MatchesTagExact(AbilityInputAction.InputTag))
		{
			return AbilityInputAction.InputAction;
		}
	}
	
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find AbilityInputAction for InputTag [%s], on InputConfig [%s]"), *InputTag.ToString(), *GetNameSafe(this))
	}
	
	return nullptr;
}
