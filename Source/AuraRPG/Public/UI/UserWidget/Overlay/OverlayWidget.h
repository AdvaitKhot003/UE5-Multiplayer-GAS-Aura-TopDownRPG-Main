// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "UI/UserWidget/AuraUserWidget.h"
#include "OverlayWidget.generated.h"

class UGlobeProgressBarWidget;
class UOverlayWidgetController;

UCLASS()
class AURARPG_API UOverlayWidget : public UAuraUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void WidgetControllerSet_Implementation() override;
	
protected:
	virtual void NativePreConstruct() override;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UGlobeProgressBarWidget> HealthGlobeWidget;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UGlobeProgressBarWidget> ManaGlobeWidget;
	
	UPROPERTY(BlueprintReadOnly, Category = "Aura|UserWidget")
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
};
