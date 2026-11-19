// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "UI/UserWidget/Template/AuraSizeBoxWidget.h"
#include "ButtonWidget.generated.h"

class UImage;
class UButton;
class UTextBlock;

DECLARE_MULTICAST_DELEGATE(FOnButtonWidgetClicked);

UCLASS()
class AURARPG_API UButtonWidget : public UAuraSizeBoxWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aura|Button")
	FText ButtonText;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aura|Button")
	FSlateFontInfo FontStyle;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aura|Button")
	FSlateBrush ButtonBorderBrush;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aura|Button")
	FSlateBrush ButtonNormalBrush;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aura|Button")
	FSlateBrush ButtonHoveredBrush;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aura|Button")
	FSlateBrush ButtonPressedBrush;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aura|Button")
	FSlateBrush ButtonDisabledBrush;
	
	FOnButtonWidgetClicked OnButtonClicked;
	
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeOnInitialized() override;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> Image_ButtonBorder;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> Button_Default;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> TextBlock_Button;
	
private:
	UFUNCTION()
	void HandleButtonClicked() const;
};
