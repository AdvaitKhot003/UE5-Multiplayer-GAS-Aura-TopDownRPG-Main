// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "AuraWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "OverlayWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangeSignature, float, NewValue);

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
	
private:
	void HealthChanged(const FOnAttributeChangeData& Data) const;
	void MaxHealthChanged(const FOnAttributeChangeData& Data) const;
	void ManaChanged(const FOnAttributeChangeData& Data) const;
	void MaxManaChanged(const FOnAttributeChangeData& Data) const;
};
