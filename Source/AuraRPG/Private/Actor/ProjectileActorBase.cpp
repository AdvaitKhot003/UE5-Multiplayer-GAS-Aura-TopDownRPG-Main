// No Copyright.

#include "Actor/ProjectileActorBase.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AProjectileActorBase::AProjectileActorBase()
{
	SetReplicates(true);
	SetReplicateMovement(true);
	
	PrimaryActorTick.bCanEverTick = false;
	InitialLifeSpan = 5.f;
	
	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SetRootComponent(SphereCollision);
	
	SphereCollision->SetSphereRadius(20.f);
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereCollision->SetCollisionObjectType(ECC_WorldDynamic);
	SphereCollision->SetGenerateOverlapEvents(true);
	SphereCollision->SetNotifyRigidBodyCollision(true);
	
	FCollisionResponseContainer CollisionResponses;
	CollisionResponses.SetAllChannels(ECR_Ignore);
	CollisionResponses.SetResponse(ECC_WorldStatic, ECR_Block);
	CollisionResponses.SetResponse(ECC_WorldDynamic, ECR_Overlap);
	CollisionResponses.SetResponse(ECC_Pawn, ECR_Overlap);
	SphereCollision->SetCollisionResponseToChannels(CollisionResponses);
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComp");
	ProjectileMovement->InitialSpeed = 500.f;
	ProjectileMovement->MaxSpeed = 500.f;
	ProjectileMovement->ProjectileGravityScale = 0.f;
}

bool AProjectileActorBase::IsNetRelevantFor(
	const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const
{
	if (GetInstigator() && RealViewer && RealViewer == GetInstigator()->GetController())
	{
		return false;
	}
	return Super::IsNetRelevantFor(RealViewer, ViewTarget, SrcLocation);
}

void AProjectileActorBase::BeginPlay()
{
	Super::BeginPlay();
	
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AProjectileActorBase::OnSphereOverlap);
	SphereCollision->OnComponentHit.AddDynamic(this, &AProjectileActorBase::OnSphereHit);
}

void AProjectileActorBase::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!HasAuthority() || OtherActor == GetInstigator()) return;
	
	if (!bIsClient && HasAuthority())
	{
		// apply the GameplayEffectSpec to the target ASC
	}
	
	Destroy();
}

void AProjectileActorBase::OnSphereHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!HasAuthority()) return;
	Destroy();
}
