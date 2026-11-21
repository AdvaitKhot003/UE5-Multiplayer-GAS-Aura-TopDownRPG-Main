// No Copyright.

#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Data/AuraAttributeInfoDataAsset.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	check(AttributeInfoDataAsset);
	
	const UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(AttributeSet);
	if (!AuraAttributeSet) return;
	
	for (const auto& Pair : AuraAttributeSet->TagsToAttributes)
	{
		FAuraAttributeInfo AttributeInfo = AttributeInfoDataAsset->FindAttributeInfoByTag(Pair.Key);
		AttributeInfo.AttributeValue = Pair.Value().GetNumericValue(AuraAttributeSet);
		OnAttributeInfoChangeDelegate.Broadcast(AttributeInfo);
	}
}

void UAttributeMenuWidgetController::BindCallbackToDependencies()
{
	check(AttributeInfoDataAsset);
	
	const UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(AttributeSet);
	if (!AuraAttributeSet || !AbilitySystemComponent) return;
	
	for (const auto& Pair : AuraAttributeSet->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
			[this, AttributeTag = Pair.Key](const FOnAttributeChangeData& Data)
			{
				FAuraAttributeInfo AttributeInfo = AttributeInfoDataAsset->FindAttributeInfoByTag(AttributeTag);
				AttributeInfo.AttributeValue = Data.NewValue;
				OnAttributeInfoChangeDelegate.Broadcast(AttributeInfo);
			}
		);
	}
}
