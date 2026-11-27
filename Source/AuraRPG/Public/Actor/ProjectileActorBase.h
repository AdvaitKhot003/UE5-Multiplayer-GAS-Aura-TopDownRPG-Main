// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileActorBase.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class AURARPG_API AProjectileActorBase : public AActor
{
	GENERATED_BODY()
	
public:
	AProjectileActorBase();
	
	// The local client already has a visual-only (local) copy of this projectile (bIsClient),
	// so don't replicate the server's copy to them. Everyone else still receives it.
	virtual bool IsNetRelevantFor(
		const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const override;
	
	UPROPERTY(Transient)
	bool bIsClient = false;
	
protected:
	virtual void BeginPlay() override;
	
private:
	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnSphereHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
		FVector NormalImpulse, const FHitResult& Hit);
	
	UPROPERTY(VisibleAnywhere, Category = "Aura|Projectile")
	TObjectPtr<USphereComponent> SphereCollision;
	
	UPROPERTY(VisibleAnywhere, Category = "Aura|Projectile")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;
};
