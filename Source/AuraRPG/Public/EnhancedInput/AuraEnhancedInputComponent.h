// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "GameplayTagContainer.h"
#include "Data/AuraInputDataAsset.h"
#include "AuraEnhancedInputComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class AURARPG_API UAuraEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	
public:
	template<class UserObject, typename CallbackFunction>
	void BindNativeInputAction(const UAuraInputDataAsset* InInputDataAsset, const FGameplayTag& InInputTag,
		ETriggerEvent TriggerEvent, UserObject* Object, CallbackFunction Function);
	
	template<class UserObject, typename CallbackPressed, typename CallbackHeld, typename CallbackReleased>
	void BindAbilityInputAction(const UAuraInputDataAsset* InInputDataAsset, UserObject* Object,
		CallbackPressed PressedFunction, CallbackHeld HeldFunction, CallbackReleased ReleasedFunction);
};

template <class UserObject, typename CallbackFunction>
void UAuraEnhancedInputComponent::BindNativeInputAction(const UAuraInputDataAsset* InInputDataAsset,
	const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* Object, CallbackFunction Function)
{
	check(InInputDataAsset);
	
	const UInputAction* InputAction = InInputDataAsset->FindNativeInputActionByTag(InInputTag);
	if (!InputAction) return;
	BindAction(InputAction, TriggerEvent, Object, Function);
}

template <class UserObject, typename CallbackPressed, typename CallbackHeld, typename CallbackReleased>
void UAuraEnhancedInputComponent::BindAbilityInputAction(const UAuraInputDataAsset* InInputDataAsset,
	UserObject* Object, CallbackPressed PressedFunction, CallbackHeld HeldFunction, CallbackReleased ReleasedFunction)
{
	check(InInputDataAsset);
	
	for (const FAuraInputAction& InputConfig : InInputDataAsset->AbilityInputActions)
	{
		if (!InputConfig.IsValid()) continue;
		
		BindAction(InputConfig.InputAction, ETriggerEvent::Started,   Object, PressedFunction,  InputConfig.InputTag);
		BindAction(InputConfig.InputAction, ETriggerEvent::Triggered, Object, HeldFunction,     InputConfig.InputTag);
		BindAction(InputConfig.InputAction, ETriggerEvent::Completed, Object, ReleasedFunction, InputConfig.InputTag);
		BindAction(InputConfig.InputAction, ETriggerEvent::Canceled,  Object, ReleasedFunction, InputConfig.InputTag);
	}
}
