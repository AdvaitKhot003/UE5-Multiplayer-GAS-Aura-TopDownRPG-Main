// No Copyright.

#include "UI/UserWidget/Overlay/OverlayWidget.h"
#include "UI/UserWidget/ProgressBar/GlobeProgressBarWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "UI/UserWidget/Overlay/Message/MessageWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"

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
	
	OverlayWidgetController->UIMessageWidgetRowDelegate.AddUObject(this, &UOverlayWidget::UIMessageWidgetRowReceived);
}

void UOverlayWidget::UIMessageWidgetRowReceived(FUIMessageWidgetRow Row) const
{
	if (!Row.MessageWidget) return;
	
	UMessageWidget* MessageWidget = CreateWidget<UMessageWidget>(GetOwningPlayer(), Row.MessageWidget);
	if (!MessageWidget) return;
	
	MessageWidget->SetMessageIconAndText(Row.MessageIcon, Row.MessageText);
	MessageWidget->SetAlignmentInViewport(FVector2D(0.5f, 0.5f));
	
	const FVector2D ViewportSize = UWidgetLayoutLibrary::GetViewportSize(this);
	MessageWidget->SetPositionInViewport(ViewportSize * 0.5f, true);
	
	MessageWidget->AddToViewport();
}
