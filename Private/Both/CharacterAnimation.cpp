// Fill out your copyright notice in the Description page of Project Settings.


#include "Both/CharacterAnimation.h"
#include "KismetAnimationLibrary.h"


void UCharacterAnimation::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* Pawn = TryGetPawnOwner();

	if (Pawn) {
		//IsValid
		Velocity = Pawn->GetVelocity().Size();
		Direction = UKismetAnimationLibrary::CalculateDirection(Pawn->GetVelocity(), Pawn->GetActorRotation());

	}
	else {
		//IsNotValid
		PreviewWindowUpdate_Implementation();
	}
}
UCharacterAnimation::UCharacterAnimation() : Velocity(0.0f), Direction(0.0f), DebugFire(false),
DebugHit(false), DebugDeath(false), CurrentDeathAsset(nullptr), ActionSlotName("Action")
{
}

void UCharacterAnimation::FireAnimation_Implementation()
{
	
	if (FireAsset)
	{
		PlaySlotAnimationAsDynamicMontage(FireAsset, ActionSlotName);
	}
	
	
}

void UCharacterAnimation::HitAnimation_Implementation(float notUsed)
{
	if (HitAsset)
	{
		PlaySlotAnimationAsDynamicMontage(HitAsset, ActionSlotName);
	}
}

void UCharacterAnimation::DeathAnimation_Implementation()
{
	if (DeathAssets.Num() > 0)
	{
		CurrentDeathAsset = DeathAssets[FMath::RandRange(0, DeathAssets.Num() - 1)];
		//PlaySlotAnimationAsDynamicMontage(CurrentDeathAsset, ActionSlotName);
		// Get animation duration
		const float AnimDuration = CurrentDeathAsset->GetPlayLength();
		FTimerHandle DeathEndTimerHandle;
		// Set timer to call DeathEnded after the animation duration
		if (UWorld* World = GetWorld())
		{
			World->GetTimerManager().SetTimer(
				DeathEndTimerHandle,
				this,
				&UCharacterAnimation::DeathEnded,
				AnimDuration,
				false
			);
		}
	}
}

void UCharacterAnimation::ReloadAnimation_Implementation()
{
	if (ReloadAsset) {
		PlaySlotAnimationAsDynamicMontage(ReloadAsset, ActionSlotName);
	}
}


void UCharacterAnimation::PreviewWindowUpdate_Implementation()
{
	if (DebugFire)
	{
		DebugFire = false;
		FireAnimation();
	}

	if (DebugHit)
	{
		DebugHit = false;
		HitAnimation();
	}

	if (DebugDeath)
	{
		DebugDeath = false;
		DeathAnimation();
	}
	if (DebugReload)
	{
		DebugReload = false;
		ReloadAnimation();
	}
}

void UCharacterAnimation::DeathEnded()
{
	OnDeathEnded.Broadcast();
}

