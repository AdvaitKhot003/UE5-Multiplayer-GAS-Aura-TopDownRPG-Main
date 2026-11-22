// No Copyright.

#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(AttributeSet);
	if (!AuraAttributeSet) return;
	
	for (const auto& Pair : AuraAttributeSet->TagsToAttributes)
	{
		OnAttributeValueChangeDelegate.Broadcast(Pair.Key, Pair.Value().GetNumericValue(AuraAttributeSet));
	}
}

void UOverlayWidgetController::BindCallbackToDependencies()
{
	const UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(AttributeSet);
	if (!AuraAttributeSet || !AbilitySystemComponent) return;
	
	for (const auto& Pair : AuraAttributeSet->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
			[this, AttributeTag = Pair.Key](const FOnAttributeChangeData& Data){
				OnAttributeValueChangeDelegate.Broadcast(AttributeTag, Data.NewValue);
		});
	}
	
	UAuraAbilitySystemComponent* AuraAbilitySystemComp = Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent);
	if (!AuraAbilitySystemComp) return;
	AuraAbilitySystemComp->GameplayEffectAssetTagsDelegate.AddUObject(this, &ThisClass::GameplayEffectAssetTagsReceived);
}

void UOverlayWidgetController::GameplayEffectAssetTagsReceived(const FGameplayTagContainer& AssetTags) const
{
	if (AssetTags.IsEmpty()) return;
	
	static const FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
	
	for (const FGameplayTag& AssetTag : AssetTags)
	{
		if (!AssetTag.MatchesTag(MessageTag)) continue;
		
		const FUIMessageWidgetRow* Row = FindDataTableRowByTag<FUIMessageWidgetRow>(UIMessageWidgetDataTable, AssetTag);
		if (!Row) continue;
		UIMessageWidgetRowDelegate.Broadcast(*Row);
	}
}
