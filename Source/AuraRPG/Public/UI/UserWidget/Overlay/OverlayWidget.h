// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "UI/UserWidget/AuraUserWidget.h"
#include "OverlayWidget.generated.h"

class UGlobeProgressBarWidget;

UCLASS()
class AURARPG_API UOverlayWidget : public UAuraUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativePreConstruct() override;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UGlobeProgressBarWidget> HealthGlobeWidget;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UGlobeProgressBarWidget> ManaGlobeWidget;
};
