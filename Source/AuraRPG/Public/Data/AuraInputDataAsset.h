// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AuraInputDataAsset.generated.h"

class UInputAction;
class UInputMappingContext;

USTRUCT(BlueprintType)
struct FAuraInputAction
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, meta = (Categories = "Input"))
	FGameplayTag InputTag = FGameplayTag();
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> InputAction = nullptr;
	
	bool IsValid() const { return InputTag.IsValid() && InputAction != nullptr; }
};

UCLASS()
class AURARPG_API UAuraInputDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, Category = "Aura|EnhancedInput")
	TArray<TObjectPtr<UInputMappingContext>> InputMappingContexts;
	
	UPROPERTY(EditDefaultsOnly, Category = "Aura|EnhancedInput|InputAction", meta = (TitleProperty = "InputTag"))
	TArray<FAuraInputAction> NativeInputActions;
	
	UPROPERTY(EditDefaultsOnly, Category = "Aura|EnhancedInput|InputAction", meta = (TitleProperty = "InputTag"))
	TArray<FAuraInputAction> AbilityInputActions;
	
	UInputAction* FindNativeInputActionByTag(const FGameplayTag& InInputTag) const;
	UInputAction* FindAbilityInputActionByTag(const FGameplayTag& InInputTag) const;
};
