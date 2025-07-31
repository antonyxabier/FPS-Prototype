// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CodeGameMode.generated.h"

class UCodeResultsWidget;

/**
 * 
 */
UCLASS()
class END2503AC_API ACodeGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACodeGameMode();

	UFUNCTION(BlueprintCallable)
	void AddEnemy(AActor* EnemyActor);

	virtual void BeginPlay() override;

	UPROPERTY()
	class ABasePlayer* CurrentPlayer;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCodeResultsWidget> ResultsWidgetClass;

	UPROPERTY()
	UCodeResultsWidget* ResultsWidgetObj;

	UPROPERTY()
	int CurrentEnemyCount;

private:
	int NumberOfEnemies;

	UFUNCTION(BlueprintCallable)
	void RemoveEnemy(AActor* DestroyedActor);

	UFUNCTION(BlueprintCallable)
	void RemovePlayer();
	
};
