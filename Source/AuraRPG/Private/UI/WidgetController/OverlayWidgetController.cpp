// No Copyright.

#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(AttributeSet);
	if (!AuraAttributeSet) return;
	
	OnHealthChangeDelegate.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChangeDelegate.Broadcast(AuraAttributeSet->GetMaxHealth());
	OnManaChangeDelegate.Broadcast(AuraAttributeSet->GetMana());
	OnMaxManaChangeDelegate.Broadcast(AuraAttributeSet->GetMaxMana());
}

void UOverlayWidgetController::BindCallbackToDependencies()
{
	const UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(AttributeSet);
	if (!AuraAttributeSet || !AbilitySystemComponent) return;
	
	UAuraAbilitySystemComponent* AuraAbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent);
	if (!AuraAbilitySystemComponent) return;
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetManaAttribute()).AddUObject(this, &UOverlayWidgetController::ManaChanged);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxManaChanged);
	
	AuraAbilitySystemComponent->GameplayEffectAssetTagsDelegate.AddUObject(
		this, &UOverlayWidgetController::GameplayEffectAssetTagsReceived);
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChangeDelegate.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChangeDelegate.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChangeDelegate.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChangeDelegate.Broadcast(Data.NewValue);
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
