// No Copyright.

#include "UI/UserWidget/AuraUserWidget.h"

void UAuraUserWidget::SetWidgetController(UObject* InWidgetController)
{
	if (!InWidgetController) return;
	
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
