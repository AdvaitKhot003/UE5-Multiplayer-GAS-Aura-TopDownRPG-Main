// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "UI/UserWidget/Template/AuraSizeBoxWidget.h"
#include "TextValueButtonRowWidget.generated.h"

class UTextBlock;
class UValueWidget;
class UButtonWidget;

UCLASS()
class AURARPG_API UTextValueButtonRowWidget : public UAuraSizeBoxWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativePreConstruct() override;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> TextBlock_Attribute;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UValueWidget> ValueWidget;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButtonWidget> ButtonWidget;
};
