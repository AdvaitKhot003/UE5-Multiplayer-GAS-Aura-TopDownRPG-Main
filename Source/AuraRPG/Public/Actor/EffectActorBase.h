// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameFramework/Actor.h"
#include "EffectActorBase.generated.h"

class USceneComponent;
class UShapeComponent;
class UGameplayEffect;
class UAbilitySystemComponent;

UENUM(BlueprintType)
enum class EEffectCollisionShape : uint8
{
	Sphere,
	Box,
	Capsule
};

UENUM(BlueprintType)
enum class EEffectApplicationPolicy : uint8
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};

UENUM(BlueprintType)
enum class EEffectRemovalPolicy : uint8
{
	RemoveOnEndOverlap,
	DoNotRemove
};

UCLASS()
class AURARPG_API AEffectActorBase : public AActor
{
	GENERATED_BODY()
	
public:
	AEffectActorBase();
	
	virtual void OnConstruction(const FTransform& Transform) override;
	
protected:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	void BeginOverlap(AActor* TargetActor);
	void EndOverlap(AActor* TargetActor);
	
private:
	void ApplyEffectSpecToTarget(AActor* TargetActor, const TSubclassOf<UGameplayEffect>& GameplayEffectClass);
	void RemoveActiveEffectFromTarget(AActor* TargetActor);
	
	void ClearEffectCollision();
	void CreateEffectCollision();
	void ConfigureEffectCollision();
	
	UPROPERTY(VisibleAnywhere, Category = "Aura|Effects")
	TObjectPtr<USceneComponent> EffectRoot;
	
#pragma region Collision Types
	UPROPERTY(EditDefaultsOnly, Category = "Aura|Collision")
	EEffectCollisionShape EffectCollisionShape = EEffectCollisionShape::Sphere;
	
	UPROPERTY(EditDefaultsOnly, Category = "Aura|Collision",
		meta = (EditCondition = "EffectCollisionShape == EEffectCollisionShape::Sphere"))
	float SphereRadius = 100.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Aura|Collision",
		meta = (EditCondition = "EffectCollisionShape == EEffectCollisionShape::Box"))
	FVector BoxExtent = FVector(100.f);
	
	UPROPERTY(EditDefaultsOnly, Category = "Aura|Collision",
		meta = (EditCondition = "EffectCollisionShape == EEffectCollisionShape::Capsule"))
	float CapsuleRadius = 50.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Aura|Collision",
		meta = (EditCondition = "EffectCollisionShape == EEffectCollisionShape::Capsule"))
	float CapsuleHalfHeight = 100.f;
	
	UPROPERTY(VisibleAnywhere, Category = "Aura|Collision")
	TObjectPtr<UShapeComponent> EffectCollision;
#pragma endregion
	
	UPROPERTY(EditAnywhere, Category = "Aura|Effects")
	float EffectLevel = 1.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Aura|Effects")
	bool bDestroyOnOverlap = false;
	
	UPROPERTY(EditDefaultsOnly, Category = "Aura|Effects")
	bool bDestroyOnEndOverlap = false;
	
	UPROPERTY(Transient)
	TMap<FActiveGameplayEffectHandle, TWeakObjectPtr<UAbilitySystemComponent>> ActiveEffectHandles;
	
#pragma region Instant Gameplay Effect
	UPROPERTY(EditDefaultsOnly, Category = "Aura|Effects|InstantEffect")
	EEffectApplicationPolicy InstantApplicationPolicy = EEffectApplicationPolicy::DoNotApply;
	
	UPROPERTY(EditDefaultsOnly, Category = "Aura|Effects|InstantEffect",
		meta = (EditCondition = "InstantApplicationPolicy != EEffectApplicationPolicy::DoNotApply"))
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;
#pragma endregion
	
#pragma region Duration Gameplay Effect
	UPROPERTY(EditDefaultsOnly, Category = "Aura|Effects|DurationEffect")
	EEffectApplicationPolicy DurationApplicationPolicy = EEffectApplicationPolicy::DoNotApply;
	
	UPROPERTY(EditDefaultsOnly, Category = "Aura|Effects|DurationEffect",
		meta = (EditCondition = "DurationApplicationPolicy != EEffectApplicationPolicy::DoNotApply"))
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;
#pragma endregion
	
#pragma region Infinite Gameplay Effect
	UPROPERTY(EditDefaultsOnly, Category = "Aura|Effects|InfiniteEffect")
	EEffectApplicationPolicy InfiniteApplicationPolicy = EEffectApplicationPolicy::DoNotApply;
	
	UPROPERTY(EditDefaultsOnly, Category = "Aura|Effects|InfiniteEffect",
		meta = (EditCondition = "InfiniteApplicationPolicy != EEffectApplicationPolicy::DoNotApply"))
	EEffectRemovalPolicy InfiniteRemovalPolicy = EEffectRemovalPolicy::DoNotRemove;
	
	UPROPERTY(EditDefaultsOnly, Category = "Aura|Effects|InfiniteEffect",
		meta = (EditCondition = "InfiniteApplicationPolicy != EEffectApplicationPolicy::DoNotApply"))
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Aura|Effects|InfiniteEffect",
		meta = (EditCondition = "InfiniteRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap"))
	int32 StacksToRemove = -1;
#pragma endregion
};
