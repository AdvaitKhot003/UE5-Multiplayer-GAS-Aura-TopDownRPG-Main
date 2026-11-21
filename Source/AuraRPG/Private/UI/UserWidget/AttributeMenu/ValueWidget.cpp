// No Copyright.

#include "UI/UserWidget/AttributeMenu/ValueWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UValueWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	if (!Image_Background || !Image_Frame) return;
	
	Image_Background->SetBrush(BackgroundBrush);
	Image_Frame->SetBrush(FrameBrush);
}

void UValueWidget::SetAttributeValue(float AttributeValue) const
{
	if (!TextBlock_Value) return;
	TextBlock_Value->SetText(FText::AsNumber(AttributeValue));
}
