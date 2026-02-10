


#include "Actor/AuraEffectActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Components/SphereComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Components/StaticMeshComponent.h"


AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("RootSceneComponent"));
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	
	if (!TargetASC) return;
	
	checkf(GameplayEffectClass, TEXT("GameplayEffectClass need initialization in EffectActor"));
	
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	
	FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, ActorLevel, EffectContextHandle);
	
	FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	
	const bool bIsInfinite = EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
	if (bIsInfinite && InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::ERP_RemoveOnEndOverlap)
	{
		ActiveEffectHandles.FindOrAdd(TargetASC).HandleList.Add(ActiveEffectHandle);
	}
}

void AAuraEffectActor::OnOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::EAP_ApplyOnOverlap)
	{
		for (auto& InstantGameplayEffectClass : InstantGameplayEffectClasses)
		{
			ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
		}
	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::EAP_ApplyOnOverlap)
	{
		for (auto& DurationGameplayEffectClass : DurationGameplayEffectClasses)
		{
			ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
		}
	}
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::EAP_ApplyOnOverlap)
	{
		for (auto& InfiniteGameplayEffectClass : InfiniteGameplayEffectClasses)
		{
			ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
		}
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::EAP_ApplyOnEndOverlap)
	{
		for (auto& InstantGameplayEffectClass : InstantGameplayEffectClasses)
		{
			ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
		}
	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::EAP_ApplyOnEndOverlap)
	{
		for (auto& DurationGameplayEffectClass : DurationGameplayEffectClasses)
		{
			ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
		}
	}
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::EAP_ApplyOnEndOverlap)
	{
		for (auto& InfiniteGameplayEffectClass : InfiniteGameplayEffectClasses)
		{
			ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
		}
	}
	if (InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::ERP_RemoveOnEndOverlap)
	{
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if (!IsValid(TargetASC)) return;
		
		if (FActiveEffectHandles* HandlesStruct = ActiveEffectHandles.Find(TargetASC))
		{
			for (auto& Handle : HandlesStruct->HandleList)
			{
				TargetASC->RemoveActiveGameplayEffect(Handle);
			}
			
			ActiveEffectHandles.Remove(TargetASC);
		}
		
		/*TArray<UAbilitySystemComponent*> HandlesToRemove;
		for (auto HandlePair :ActiveEffectHandles)
		{
			if (TargetASC == HandlePair.Key)
			{
				for (auto& InfiniteGameplayEffect : HandlePair.Value.HandleList)
				{
					TargetASC->RemoveActiveGameplayEffect(InfiniteGameplayEffect, 1);
				}
				
				HandlesToRemove.Add(HandlePair.Key);
			}
		}
		
		for (auto& Handle : HandlesToRemove)
		{
			ActiveEffectHandles.FindAndRemoveChecked(Handle);
		}*/
	}
}
