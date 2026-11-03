// No Copyright.

#include "Data/AuraInputDataAsset.h"

UInputAction* UAuraInputDataAsset::FindNativeInputActionByTag(const FGameplayTag& InInputTag) const
{
	if (!InInputTag.IsValid()) return nullptr;
	
	for (const FAuraInputAction& InputConfig : NativeInputActions)
	{
		if (!InputConfig.IsValid() || !InputConfig.InputTag.MatchesTagExact(InInputTag)) continue;
		return InputConfig.InputAction;
	}
	return nullptr;
}

UInputAction* UAuraInputDataAsset::FindAbilityInputActionByTag(const FGameplayTag& InInputTag) const
{
	if (!InInputTag.IsValid()) return nullptr;
	
	for (const FAuraInputAction& InputConfig : AbilityInputActions)
	{
		if (!InputConfig.IsValid() || !InputConfig.InputTag.MatchesTagExact(InInputTag)) continue;
		return InputConfig.InputAction;
	}
	return nullptr;
}
