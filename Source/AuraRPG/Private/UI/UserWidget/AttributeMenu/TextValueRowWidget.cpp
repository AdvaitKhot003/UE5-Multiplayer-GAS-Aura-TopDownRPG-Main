// No Copyright.

#include "UI/UserWidget/AttributeMenu/TextValueRowWidget.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Components/TextBlock.h"
#include "Data/AuraAttributeInfoDataAsset.h"
#include "UI/UserWidget/AttributeMenu/ValueWidget.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"

void UTextValueRowWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UTextValueRowWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	AttributeMenuWidgetController = UAuraAbilitySystemLibrary::GetAttributeMenuWidgetController(this);
	if (AttributeMenuWidgetController)
	{
		SetWidgetController(AttributeMenuWidgetController);
	}
}

void UTextValueRowWidget::WidgetControllerSet_Implementation()
{
	if (!AttributeMenuWidgetController) return;
	AttributeMenuWidgetController->OnAttributeInfoChangeDelegate.AddUObject(this, &ThisClass::AttributeInfoChangeReceived);
}

void UTextValueRowWidget::AttributeInfoChangeReceived(const FAuraAttributeInfo& AttributeInfo) const
{
	if (!AttributeInfo.AttributeTag.MatchesTagExact(AttributeTag)) return;
	SetAttributeNameAndValue(AttributeInfo.AttributeName, AttributeInfo.AttributeValue);
}

void UTextValueRowWidget::SetAttributeNameAndValue(const FText& AttributeName, float AttributeValue) const
{
	if (TextBlock_Attribute && !AttributeName.IsEmpty())
	{
		TextBlock_Attribute->SetText(AttributeName);
	}
	
	if (ValueWidget)
	{
		ValueWidget->SetAttributeValue(AttributeValue);
	}
}
