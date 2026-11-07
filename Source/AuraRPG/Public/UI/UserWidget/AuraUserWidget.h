// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidget.generated.h"

UCLASS()
class AURARPG_API UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);
	
	UObject* GetWidgetController() const { return WidgetController; }
	
	UFUNCTION(BlueprintNativeEvent)
	void WidgetControllerSet();
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Aura|UserWidget")
	TObjectPtr<UObject> WidgetController;
};
