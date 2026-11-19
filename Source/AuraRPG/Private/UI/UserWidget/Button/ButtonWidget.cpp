// No Copyright.

#include "UI/UserWidget/Button/ButtonWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UButtonWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	if (!Image_ButtonBorder || !Button_Default || !TextBlock_Button) return;
	
	Image_ButtonBorder->SetBrush(ButtonBorderBrush);
	
	TextBlock_Button->SetText(ButtonText);
	TextBlock_Button->SetFont(FontStyle);
	
	FButtonStyle ButtonStyle;
	ButtonStyle.SetNormal(ButtonNormalBrush);
	ButtonStyle.SetHovered(ButtonHoveredBrush);
	ButtonStyle.SetPressed(ButtonPressedBrush);
	ButtonStyle.SetDisabled(ButtonDisabledBrush);
	Button_Default->SetStyle(ButtonStyle);
}

void UButtonWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	if (!Button_Default) return;
	Button_Default->OnClicked.AddDynamic(this, &UButtonWidget::HandleButtonClicked);
}

void UButtonWidget::HandleButtonClicked() const
{
	OnButtonClicked.Broadcast();
}
