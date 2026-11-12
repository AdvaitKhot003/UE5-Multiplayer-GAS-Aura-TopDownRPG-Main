// No Copyright.

#include "UI/UserWidget/Overlay/Message/MessageWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UMessageWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UMessageWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (!MessageAnimation) return;
	
	FWidgetAnimationDynamicEvent FinishedEvent;
	FinishedEvent.BindDynamic(this, &UMessageWidget::OnMessageAnimationFinished);
	BindToAnimationFinished(MessageAnimation, FinishedEvent);
	
	PlayAnimation(MessageAnimation);
}

void UMessageWidget::OnMessageAnimationFinished()
{
	RemoveFromParent();
}

void UMessageWidget::SetMessageIconAndText(UTexture2D* MessageIcon, const FText& MessageText) const
{
	if (Image_MessageIcon && MessageIcon)
	{
		Image_MessageIcon->SetBrushFromTexture(MessageIcon);
	}
	
	if (Text_Message && !MessageText.IsEmpty())
	{
		Text_Message->SetText(MessageText);
	}
}
