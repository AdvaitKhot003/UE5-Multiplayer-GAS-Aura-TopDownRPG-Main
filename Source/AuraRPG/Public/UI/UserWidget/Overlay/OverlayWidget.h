// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "UI/UserWidget/AuraUserWidget.h"
#include "OverlayWidget.generated.h"

class UGlobeProgressBarWidget;
class UOverlayWidgetController;
class UButtonWidget;
class UAttributeMenuWidget;
struct FUIMessageWidgetRow;

UCLASS()
class AURARPG_API UOverlayWidget : public UAuraUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void WidgetControllerSet_Implementation() override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Aura|Overlay")
	FMargin AttributeMenuPadding = FMargin(20.f);
	
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeOnInitialized() override;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UGlobeProgressBarWidget> HealthGlobeWidget;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UGlobeProgressBarWidget> ManaGlobeWidget;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButtonWidget> AttributeMenuButtonWidget;
	
	UPROPERTY(BlueprintReadOnly, Category = "Aura|Overlay")
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	
private:
	void UIMessageWidgetRowReceived(FUIMessageWidgetRow Row) const;
	
	UFUNCTION()
	void OnAttributeMenuButtonClicked();
	
	UPROPERTY(EditDefaultsOnly, Category = "Aura|Overlay")
	TSubclassOf<UAttributeMenuWidget> AttributeMenuWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UAttributeMenuWidget> AttributeMenuWidget;
	
	void OnAttributeMenuClosed() const;
};
