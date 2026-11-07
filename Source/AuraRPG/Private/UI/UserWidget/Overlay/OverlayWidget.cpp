// No Copyright.

#include "UI/UserWidget/Overlay/OverlayWidget.h"
#include "UI/UserWidget/ProgressBar/GlobeProgressBarWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"

void UOverlayWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UOverlayWidget::WidgetControllerSet_Implementation()
{
	if (!WidgetController) return;
	
	OverlayWidgetController = Cast<UOverlayWidgetController>(WidgetController);
	if (!OverlayWidgetController) return;
	
	if (!HealthGlobeWidget || !ManaGlobeWidget) return;
	HealthGlobeWidget->SetWidgetController(OverlayWidgetController);
	ManaGlobeWidget->SetWidgetController(OverlayWidgetController);
}
