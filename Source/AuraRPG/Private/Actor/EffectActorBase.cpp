// No Copyright.

#include "Actor/EffectActorBase.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

AEffectActorBase::AEffectActorBase()
{
	PrimaryActorTick.bCanEverTick = false;
	
	EffectRoot = CreateDefaultSubobject<USceneComponent>("SceneComp");
	SetRootComponent(EffectRoot);
}

void AEffectActorBase::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	
	ClearEffectCollision();
	CreateEffectCollision();
	ConfigureEffectCollision();
}

void AEffectActorBase::ClearEffectCollision()
{
	if (!EffectCollision) return;
	
	RemoveInstanceComponent(EffectCollision);
		
	EffectCollision->DestroyComponent();
	EffectCollision = nullptr;
}

void AEffectActorBase::CreateEffectCollision()
{
	switch (EffectCollisionShape)
	{
		case EEffectCollisionShape::Sphere:
		{
			USphereComponent* SphereComponent = NewObject<USphereComponent>(this);
			SphereComponent->InitSphereRadius(SphereRadius);
			EffectCollision = SphereComponent;
			break;
		}
		case EEffectCollisionShape::Box:
		{
			UBoxComponent* BoxComponent = NewObject<UBoxComponent>(this);
			BoxComponent->InitBoxExtent(BoxExtent);
			EffectCollision = BoxComponent;
			break;
		}
		case EEffectCollisionShape::Capsule:
		{
			UCapsuleComponent* CapsuleComponent = NewObject<UCapsuleComponent>(this);
			CapsuleComponent->InitCapsuleSize(CapsuleRadius, CapsuleHalfHeight);
			EffectCollision = CapsuleComponent;
			break;
		}
		default:
		{
			EffectCollision = nullptr;
			break;
		}
	}
}

void AEffectActorBase::ConfigureEffectCollision()
{
	if (!EffectCollision) return;
	
	AddInstanceComponent(EffectCollision);
	
	EffectCollision->SetupAttachment(EffectRoot);
	
	EffectCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	EffectCollision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	EffectCollision->SetGenerateOverlapEvents(true);
	
	EffectCollision->OnComponentBeginOverlap.AddDynamic(this, &AEffectActorBase::OnBeginOverlap);
	EffectCollision->OnComponentEndOverlap.AddDynamic(this, &AEffectActorBase::OnEndOverlap);
	
	EffectCollision->RegisterComponent();
}

void AEffectActorBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor) return;
	BeginOverlap(OtherActor);
}

void AEffectActorBase::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor) return;
	EndOverlap(OtherActor);
}

void AEffectActorBase::BeginOverlap(AActor* TargetActor)
{
	if (!TargetActor) return;
	
	if (InstantApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		check(InstantGameplayEffectClass);
		ApplyEffectSpecToTarget(TargetActor, InstantGameplayEffectClass);
	}
	
	if (DurationApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		check(DurationGameplayEffectClass);
		ApplyEffectSpecToTarget(TargetActor, DurationGameplayEffectClass);
	}
	
	if (InfiniteApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		check(InfiniteGameplayEffectClass);
		ApplyEffectSpecToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
	
	if (bDestroyOnOverlap == true)
	{
		Destroy();
	}
}

void AEffectActorBase::EndOverlap(AActor* TargetActor)
{
	if (!TargetActor) return;
	
	if (InstantApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		check(InstantGameplayEffectClass);
		ApplyEffectSpecToTarget(TargetActor, InstantGameplayEffectClass);
	}
	
	if (DurationApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		check(DurationGameplayEffectClass);
		ApplyEffectSpecToTarget(TargetActor, DurationGameplayEffectClass);
	}
	
	if (InfiniteApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		check(InfiniteGameplayEffectClass);
		ApplyEffectSpecToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
	
	if (InfiniteRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		RemoveActiveEffectFromTarget(TargetActor);
	}
	
	if (bDestroyOnEndOverlap == true)
	{
		Destroy();
	}
}

void AEffectActorBase::ApplyEffectSpecToTarget(AActor* TargetActor, const TSubclassOf<UGameplayEffect>& GameplayEffectClass)
{
	if (!HasAuthority() || !TargetActor || !GameplayEffectClass) return;
	
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (!TargetASC) return;
	
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	
	const FGameplayEffectSpecHandle EffectSpecHandle =
		TargetASC->MakeOutgoingSpec(GameplayEffectClass, EffectLevel, EffectContextHandle);
	if (!EffectSpecHandle.IsValid()) return;
	
	const FGameplayEffectSpec* EffectSpec = EffectSpecHandle.Data.Get();
	if (!EffectSpec) return;
	
	const UGameplayEffect* GameplayEffect = EffectSpec->Def.Get();
	if (!GameplayEffect) return;
	const bool bIsInfinite = GameplayEffect->DurationPolicy == EGameplayEffectDurationType::Infinite;
	
	const FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpec);
	if (!ActiveEffectHandle.IsValid()) return;
	
	if (bIsInfinite && InfiniteRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		ActiveEffectHandles.Add(ActiveEffectHandle, TargetASC);
	}
}

void AEffectActorBase::RemoveActiveEffectFromTarget(AActor* TargetActor)
{
	if (!HasAuthority() || !TargetActor) return;
	
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (!TargetASC) return;
	
	TArray<FActiveGameplayEffectHandle> ActiveEffectHandlesToRemove;
	
	for (const auto& HandlePair : ActiveEffectHandles)
	{
		if (HandlePair.Value.Get() != TargetASC) continue;
		
		TargetASC->RemoveActiveGameplayEffect(HandlePair.Key, StacksToRemove);
		ActiveEffectHandlesToRemove.Add(HandlePair.Key);
	}
	
	for (const FActiveGameplayEffectHandle& HandleToRemove : ActiveEffectHandlesToRemove)
	{
		ActiveEffectHandles.Remove(HandleToRemove);
	}
}
