// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseAgent.h"
#include "CodeSpawner.generated.h"

UCLASS()
class END2503AC_API ACodeSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACodeSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Defaults)
	class UStaticMeshComponent* SpawnerMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ABaseAgent> AgentToSpawn;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Health)
	class UHealthComponent* HealthComponent;

	UFUNCTION()
	void OnSpawnerDeath(float ratio);

private:
	void SpawnAgent();

};
