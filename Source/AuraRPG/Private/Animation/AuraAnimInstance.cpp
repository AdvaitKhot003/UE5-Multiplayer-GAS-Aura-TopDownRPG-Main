// No Copyright.

#include "Animation/AuraAnimInstance.h"
#include "Character/AuraCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"

void UAuraAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	AuraCharacterBase = Cast<AAuraCharacterBase>(TryGetPawnOwner());
	if (!AuraCharacterBase) return;
	
	AuraMovementComponent = AuraCharacterBase->GetCharacterMovement();
}

void UAuraAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	if (!AuraCharacterBase || !AuraMovementComponent) return;
	
	CachedGroundSpeed = AuraCharacterBase->GetVelocity().Size2D();
	bCachedHasAcceleration = AuraMovementComponent->GetCurrentAcceleration().SizeSquared2D() > SMALL_NUMBER;
}

void UAuraAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
	
	GroundSpeed = CachedGroundSpeed;
	bHasAcceleration = bCachedHasAcceleration;
}
