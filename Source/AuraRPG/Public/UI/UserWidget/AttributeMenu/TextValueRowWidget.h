// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "UI/UserWidget/Template/AuraSizeBoxWidget.h"
#include "TextValueRowWidget.generated.h"

class UTextBlock;
class UValueWidget;

UCLASS()
class AURARPG_API UTextValueRowWidget : public UAuraSizeBoxWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativePreConstruct() override;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> TextBlock_Attribute;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UValueWidget> ValueWidget;
};
