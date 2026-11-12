// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "UI/UserWidget/AuraUserWidget.h"
#include "AuraHorizontalBoxWidget.generated.h"

class UHorizontalBox;

UCLASS()
class AURARPG_API UAuraHorizontalBoxWidget : public UAuraUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativePreConstruct() override;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UHorizontalBox> HorizontalBox_Root;
};
