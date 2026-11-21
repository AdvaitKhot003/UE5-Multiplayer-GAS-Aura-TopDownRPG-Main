// No Copyright.

#include "UI/UserWidget/AttributeMenu/AttributeMenuWidget.h"
#include "Components/Image.h"
#include "UI/UserWidget/Button/ButtonWidget.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"

void UAttributeMenuWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	if (!Image_Background || !Image_Border) return;
	
	Image_Background->SetBrush(BackgroundBrush);
	Image_Border->SetBrush(BorderBrush);
}

void UAttributeMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	if (CloseButtonWidget)
	{
		CloseButtonWidget->OnButtonClicked.AddUObject(this, &UAttributeMenuWidget::OnCloseButtonClicked);
	}
	
	AttributeMenuWidgetController = UAuraAbilitySystemLibrary::GetAttributeMenuWidgetController(this);
	if (AttributeMenuWidgetController)
	{
		SetWidgetController(AttributeMenuWidgetController);
	}
}

void UAttributeMenuWidget::NativeDestruct()
{
	OnAttributeMenuClosed.Broadcast();
	Super::NativeDestruct();
}

void UAttributeMenuWidget::OnCloseButtonClicked()
{
	RemoveFromParent();
}

void UAttributeMenuWidget::WidgetControllerSet_Implementation()
{
	if (!AttributeMenuWidgetController) return;
	AttributeMenuWidgetController->BroadcastInitialValues();
}
