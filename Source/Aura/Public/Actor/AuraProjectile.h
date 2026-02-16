

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "AuraProjectile.generated.h"

UCLASS()
class AURA_API AAuraProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AAuraProjectile();
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UProjectileMovementComponent> ProjectileMovement;

	
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	FGameplayEffectSpecHandle DamageEffectSpecHandle;
protected:
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	
	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherOverlappedComponent,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
private:
	
	UPROPERTY(EditDefaultsOnly)
	float LifeSpan = 9.f;
	
	bool bHit = false;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class USphereComponent> Sphere;
	
	UPROPERTY(EditAnywhere, Category = "Effect|Niagara")
	TObjectPtr<class UNiagaraSystem> ImpactEffect;
	
	UPROPERTY(EditAnywhere, Category = "Effect|SFX")
	TObjectPtr<USoundBase> ImpactSound;
	
	UPROPERTY(EditAnywhere, Category = "Effect|SFX")
	TObjectPtr<USoundBase> LoopingSound;
	
	UPROPERTY()
	TObjectPtr<UAudioComponent> LoopingSoundComponent;
};
