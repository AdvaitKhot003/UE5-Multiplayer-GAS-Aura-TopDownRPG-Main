// No Copyright.

#include "UI/UserWidget/Template/AuraSizeBoxWidget.h"
#include "Components/SizeBox.h"

void UAuraSizeBoxWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	if (!SizeBox_Root) return;
	
	SizeBox_Root->SetWidthOverride(SizeBoxWidth);
	SizeBox_Root->SetHeightOverride(SizeBoxHeight);
}
