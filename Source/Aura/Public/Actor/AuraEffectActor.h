
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "AuraEffectActor.generated.h"

UENUM(BlueprintType)
enum class EEffectApplicationPolicy : uint8
{
	EAP_ApplyOnOverlap UMETA(DisplayName = "ApplyOnOverlap"),
	EAP_ApplyOnEndOverlap UMETA(DisplayName = "ApplyOnEndOverlap"),
	EAP_DoNotApply UMETA(DisplayName = "DoNotApply")
};

UENUM(BlueprintType)
enum class EEffectRemovalPolicy : uint8
{
	ERP_RemoveOnEndOverlap UMETA(DisplayName = "RemoveOnEndOverlap"),
	ERP_DoNotRemove UMETA(DisplayName = "DoNotRemove")
};

USTRUCT()
struct FActiveEffectHandles
{
	GENERATED_BODY()
	
	UPROPERTY()
	TArray<FActiveGameplayEffectHandle> HandleList;
};


UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AAuraEffectActor();
	

	
protected:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<class UGameplayEffect> GameplayEffectClass);
	
	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* TargetActor);
	
	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	bool bDestroyOnEffectRemoval = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects|Instant")
	TArray<TSubclassOf<UGameplayEffect>> InstantGameplayEffectClasses;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects|Instant")
	EEffectApplicationPolicy InstantEffectApplicationPolicy = EEffectApplicationPolicy::EAP_DoNotApply;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects|Duration")
	TArray<TSubclassOf<UGameplayEffect>> DurationGameplayEffectClasses;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects|Duration")
	EEffectApplicationPolicy DurationEffectApplicationPolicy = EEffectApplicationPolicy::EAP_DoNotApply;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects|Infinite")
	TArray<TSubclassOf<UGameplayEffect>> InfiniteGameplayEffectClasses;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects|Infinite")
	EEffectApplicationPolicy InfiniteEffectApplicationPolicy = EEffectApplicationPolicy::EAP_DoNotApply;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects|Infinite")
	EEffectRemovalPolicy InfiniteEffectRemovalPolicy = EEffectRemovalPolicy::ERP_RemoveOnEndOverlap;
	
	UPROPERTY()
	TMap<UAbilitySystemComponent*, FActiveEffectHandles> ActiveEffectHandles;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	float ActorLevel = 1.f;
private:


public:	

};
