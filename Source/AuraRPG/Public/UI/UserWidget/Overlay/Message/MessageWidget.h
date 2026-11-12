// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "UI/UserWidget/Template/AuraHorizontalBoxWidget.h"
#include "MessageWidget.generated.h"

class UImage;
class UTextBlock;

UCLASS()
class AURARPG_API UMessageWidget : public UAuraHorizontalBoxWidget
{
	GENERATED_BODY()
	
public:
	void SetMessageIconAndText(UTexture2D* MessageIcon, const FText& MessageText) const;
	
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> Image_MessageIcon;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Text_Message;
	
	UPROPERTY(Transient, meta=(BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> MessageAnimation;
	
private:
	UFUNCTION()
	void OnMessageAnimationFinished();
};
