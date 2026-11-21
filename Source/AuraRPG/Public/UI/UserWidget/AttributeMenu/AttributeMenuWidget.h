// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "UI/UserWidget/Template/AuraSizeBoxWidget.h"
#include "AttributeMenuWidget.generated.h"

class UButtonWidget;
class UImage;
class UAttributeMenuWidgetController;

DECLARE_MULTICAST_DELEGATE(FOnAttributeMenuClosed);

UCLASS()
class AURARPG_API UAttributeMenuWidget : public UAuraSizeBoxWidget
{
	GENERATED_BODY()
	
public:
	virtual void WidgetControllerSet_Implementation() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aura|AttributeMenu")
	FSlateBrush BackgroundBrush;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aura|AttributeMenu")
	FSlateBrush BorderBrush;
	
	FOnAttributeMenuClosed OnAttributeMenuClosed;
	
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeOnInitialized() override;
	virtual void NativeDestruct() override;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> Image_Background;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> Image_Border;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButtonWidget> CloseButtonWidget;
	
	UPROPERTY(BlueprintReadOnly, Category = "Aura|AttributeMenu")
	TObjectPtr<UAttributeMenuWidgetController> AttributeMenuWidgetController;
	
private:
	UFUNCTION()
	void OnCloseButtonClicked();
};
