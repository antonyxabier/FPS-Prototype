// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/CodeSpawner.h"
#include "Actors/BaseAgent.h"
#include "Utility/HealthComponent.h"
#include <Actors/CodeGameMode.h>

// Sets default values
ACodeSpawner::ACodeSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SpawnerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpawnerMesh"));
	SpawnerMesh->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	SpawnerMesh->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));
	SpawnerMesh->SetCollisionObjectType(ECC_Pawn);
	SpawnerMesh->SetupAttachment(RootComponent);
	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");

}

// Called when the game starts or when spawned
void ACodeSpawner::BeginPlay()
{
	Super::BeginPlay();
	SpawnAgent();
	HealthComponent->OnDeath.AddDynamic(this, &ACodeSpawner::OnSpawnerDeath);
	
}

void ACodeSpawner::OnSpawnerDeath(float ratio)
{
	UE_LOG(LogTemp, Log, TEXT("Spawner is dead!"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Spawner is dead!"));
	Destroy();
}

void ACodeSpawner::SpawnAgent()
{
	UE_LOG(LogTemp, Log, TEXT("Spawning Agent..."));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Spawning Agent..."));
	if (!AgentToSpawn) return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	FVector SpawnLocation = GetActorLocation() + FVector(0.f, 0.f, 75.f);
	FRotator SpawnRotation = FRotator::ZeroRotator;

	ABaseAgent* SpawnedAgent = GetWorld()->SpawnActor<ABaseAgent>(AgentToSpawn, SpawnLocation, SpawnRotation, SpawnParams);

	// Set timer to call again
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ACodeSpawner::SpawnAgent, SpawnRate, false);

	ACodeGameMode* GM = Cast<ACodeGameMode>(GetWorld()->GetAuthGameMode());
	if (GM)
		GM->AddEnemy(SpawnedAgent);
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to cast GameMode to ACodeGameMode"));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Failed to cast GameMode to ACodeGameMode"));
	}
}



