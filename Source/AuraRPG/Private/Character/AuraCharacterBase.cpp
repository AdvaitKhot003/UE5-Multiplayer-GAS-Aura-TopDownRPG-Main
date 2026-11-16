// No Copyright.

#include "Character/AuraCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "AbilitySystemComponent.h"

AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
	
	GetCapsuleComponent()->InitCapsuleSize(34.f, 84.f);
	
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComp");
	WeaponMesh->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AAuraCharacterBase::InitAbilityCharacterInfo()
{
	
}

UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const
{
	return nullptr;
}

void AAuraCharacterBase::InitDefaultAttributes(UAbilitySystemComponent* SourceASC)
{
	
}

void AAuraCharacterBase::ApplyEffectSpecToSelf(UAbilitySystemComponent* SourceASC,
	const TSubclassOf<UGameplayEffect>& GameplayEffectClass, float Level)
{
	if (!HasAuthority() || !SourceASC || !GameplayEffectClass) return;
	
	FGameplayEffectContextHandle EffectContextHandle = SourceASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	
	const FGameplayEffectSpecHandle EffectSpecHandle =
		SourceASC->MakeOutgoingSpec(GameplayEffectClass, Level, EffectContextHandle);
	if (!EffectSpecHandle.IsValid()) return;
	
	SourceASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
}
