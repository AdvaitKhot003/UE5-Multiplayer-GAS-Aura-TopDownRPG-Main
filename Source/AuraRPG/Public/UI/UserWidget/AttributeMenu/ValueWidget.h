// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "UI/UserWidget/Template/AuraSizeBoxWidget.h"
#include "ValueWidget.generated.h"

class UImage;
class UTextBlock;

UCLASS()
class AURARPG_API UValueWidget : public UAuraSizeBoxWidget
{
	GENERATED_BODY()
	
public:
	void SetAttributeValue(float AttributeValue) const;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aura|Value")
	FSlateBrush BackgroundBrush;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aura|Value")
	FSlateBrush FrameBrush;
	
protected:
	virtual void NativePreConstruct() override;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> Image_Background;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> Image_Frame;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> TextBlock_Value;
};
