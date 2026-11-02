// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AuraAnimInstance.generated.h"

UCLASS()
class AURARPG_API UAuraAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
};
