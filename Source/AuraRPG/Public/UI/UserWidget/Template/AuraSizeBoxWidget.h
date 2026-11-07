// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "UI/UserWidget/AuraUserWidget.h"
#include "AuraSizeBoxWidget.generated.h"

class USizeBox;

UCLASS()
class AURARPG_API UAuraSizeBoxWidget : public UAuraUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aura|SizeBox")
	float SizeBoxWidth = 100.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aura|SizeBox")
	float SizeBoxHeight = 100.f;
	
protected:
	virtual void NativePreConstruct() override;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<USizeBox> SizeBox_Root;
};
