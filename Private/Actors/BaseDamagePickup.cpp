// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseDamagePickup.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"



ABaseDamagePickup::ABaseDamagePickup() : baseDamage(2.f)
{

	particleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));

	particleSystem->SetRelativeLocation(FVector(0.0f, 0.0f, -30.0f));

	particleSystem->SetRelativeScale3D(FVector(0.4f, 0.4f, 0.25f));

	particleSystem->SetupAttachment(RootComponent);

	boxCollision->SetRelativeScale3D(FVector(1.6f, 1.6f, 1.6f));
}

void ABaseDamagePickup::HandlePickup(AActor* otherActor, FHitResult hitResult)
{
	Super::HandlePickup(otherActor, hitResult);

	UGameplayStatics::ApplyDamage(otherActor, baseDamage, NULL, this, NULL);
}

void ABaseDamagePickup::PostPickup()
{
}
