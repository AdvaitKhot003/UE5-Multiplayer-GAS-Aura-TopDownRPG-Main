// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "AuraWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "OverlayWidgetController.generated.h"

class UMessageWidget;

USTRUCT(BlueprintType)
struct FUIMessageWidgetRow : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag MessageTag = FGameplayTag();
	
	UPROPERTY(EditDefaultsOnly)
	FText MessageText = FText();
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UTexture2D> MessageIcon = nullptr;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMessageWidget> MessageWidget = nullptr;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangeSignature, float, NewValue);
DECLARE_MULTICAST_DELEGATE_OneParam(FUIMessageWidgetRowSignature, FUIMessageWidgetRow);

UCLASS()
class AURARPG_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
	
public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbackToDependencies() override;
	
	UPROPERTY(BlueprintAssignable, Category = "Aura|Attributes")
	FOnAttributeChangeSignature OnHealthChangeDelegate;
	
	UPROPERTY(BlueprintAssignable, Category = "Aura|Attributes")
	FOnAttributeChangeSignature OnMaxHealthChangeDelegate;
	
	UPROPERTY(BlueprintAssignable, Category = "Aura|Attributes")
	FOnAttributeChangeSignature OnManaChangeDelegate;
	
	UPROPERTY(BlueprintAssignable, Category = "Aura|Attributes")
	FOnAttributeChangeSignature OnMaxManaChangeDelegate;
	
	FUIMessageWidgetRowSignature UIMessageWidgetRowDelegate;
	
private:
	void HealthChanged(const FOnAttributeChangeData& Data) const;
	void MaxHealthChanged(const FOnAttributeChangeData& Data) const;
	void ManaChanged(const FOnAttributeChangeData& Data) const;
	void MaxManaChanged(const FOnAttributeChangeData& Data) const;
	
	void GameplayEffectAssetTagsReceived(const FGameplayTagContainer& AssetTags) const;
	
	UPROPERTY(EditDefaultsOnly, Category = "Aura|DataTable")
	TObjectPtr<UDataTable> UIMessageWidgetDataTable;
	
	template<typename T>
	T* FindDataTableRowByTag(const UDataTable* DataTable, const FGameplayTag& InMessageTag) const;
};

template <typename T>
T* UOverlayWidgetController::FindDataTableRowByTag(const UDataTable* DataTable, const FGameplayTag& InMessageTag) const
{
	check(DataTable);
	T* Row = DataTable->FindRow<T>(InMessageTag.GetTagName(), TEXT("FindDataTableRowByTag"));
	if (!Row) return nullptr;
	return Row;
}
