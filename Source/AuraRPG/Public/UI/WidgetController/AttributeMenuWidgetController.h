// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "AuraWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

class UAuraAttributeInfoDataAsset;
struct FAuraAttributeInfo;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnAttributeInfoChangeDelegate, const FAuraAttributeInfo&)

UCLASS()
class AURARPG_API UAttributeMenuWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
	
public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbackToDependencies() override;
	
	FOnAttributeInfoChangeDelegate OnAttributeInfoChangeDelegate;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Aura|DataAsset")
	TObjectPtr<UAuraAttributeInfoDataAsset> AttributeInfoDataAsset;
};
