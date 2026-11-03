// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AuraAnimInstance.generated.h"

class AAuraCharacterBase;
class UCharacterMovementComponent;

UCLASS()
class AURARPG_API UAuraAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Aura|Locomotion")
	float GroundSpeed = 0.f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Aura|Locomotion")
	bool bHasAcceleration = false;
	
private:
	UPROPERTY(Transient)
	TObjectPtr<AAuraCharacterBase> AuraCharacterBase;
	
	UPROPERTY(Transient)
	TObjectPtr<UCharacterMovementComponent> AuraMovementComponent;
	
	UPROPERTY(Transient)
	float CachedGroundSpeed = 0.f;
	
	UPROPERTY(Transient)
	bool bCachedHasAcceleration = false;
};
