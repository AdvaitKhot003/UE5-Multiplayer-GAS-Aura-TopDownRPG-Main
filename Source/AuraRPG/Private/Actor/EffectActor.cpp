// No Copyright.

#include "Actor/EffectActor.h"
#include "Components/SphereComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

AEffectActor::AEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	
	EffectCollision = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SetRootComponent(EffectCollision);
	EffectCollision->SetGenerateOverlapEvents(true);
	EffectCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	EffectCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	EffectCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	
	EffectMesh = CreateDefaultSubobject<UStaticMeshComponent>("EffectMesh");
	EffectMesh->SetupAttachment(GetRootComponent());
	EffectMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
	EffectCollision->OnComponentBeginOverlap.AddDynamic(this, &AEffectActor::OnBeginOverlap);
}

void AEffectActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const UAbilitySystemComponent* AbilitySystemComponent =
		UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor);
	if (!AbilitySystemComponent) return;
	
	const UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(
		AbilitySystemComponent->GetAttributeSet(UAuraAttributeSet::StaticClass()));
	if (!AuraAttributeSet) return;
	
	UAuraAttributeSet* MutableAuraAttributeSet = const_cast<UAuraAttributeSet*>(AuraAttributeSet);
	if (!MutableAuraAttributeSet) return;
	
	MutableAuraAttributeSet->SetHealth(AuraAttributeSet->GetHealth() + 25.f);
	MutableAuraAttributeSet->SetMana(AuraAttributeSet->GetMana() - 25.f);
}
