// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/CodeGameMode.h"
#include "Actors/BasePlayer.h"
#include "Actors/CodeMenuPlayerController.h"
#include "Widgets/CodeResultsWidget.h"
#include "EngineUtils.h"
#include "Actors/CodeSpawner.h"

ACodeGameMode::ACodeGameMode() :NumberOfEnemies(0), CurrentPlayer(nullptr), CurrentEnemyCount(0)
{
	PlayerControllerClass = ACodeMenuPlayerController::StaticClass();
	DefaultPawnClass = nullptr;


}

void ACodeGameMode::BeginPlay()
{
	Super::BeginPlay();
	for (TActorIterator<ABaseCharacter> It(GetWorld()); It; ++It)
	{
		ABaseCharacter* Character = *It;
		if (Character)
		{
			if (Character->IsA<ABasePlayer>())
			{
				CurrentPlayer = Cast<ABasePlayer>(Character);
				CurrentPlayer->OnPlayerLost.AddDynamic(this, &ACodeGameMode::RemovePlayer);
			}
			else
			{
				AddEnemy(Character);
			}
		}
	}
	for (TActorIterator<ACodeSpawner> It(GetWorld()); It; ++It)
	{
		ACodeSpawner* Spawner = *It;
		if (Spawner)
		{
			AddEnemy(Spawner);
		}
	}
	if (ResultsWidgetClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("ResultsWidgetClass is not NULL!"));
		ResultsWidgetObj = CreateWidget<UCodeResultsWidget>(GetWorld(), ResultsWidgetClass);
	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT("ResultsWidgetClass is NULL!"));
	}
}

void ACodeGameMode::AddEnemy(AActor* EnemyActor)
{
	if (EnemyActor)
	{
		EnemyActor->OnDestroyed.AddDynamic(this, &ACodeGameMode::RemoveEnemy);
		NumberOfEnemies++;
	}
}

void ACodeGameMode::RemoveEnemy(AActor* DestroyedActor)
{
	NumberOfEnemies--;
	if (NumberOfEnemies <= 0) {
		UE_LOG(LogTemp, Warning, TEXT("YOU WIN!"));
		GEngine->AddOnScreenDebugMessage(-1, 12.0f, FColor::Green, TEXT("YOU WIN!"));
		if (ResultsWidgetObj)
		{
			ResultsWidgetObj->AddToViewport();
			ResultsWidgetObj->SetWin();
		}
		if (CurrentPlayer) {
			CurrentPlayer->PlayerWin();
		}
	}
}

void ACodeGameMode::RemovePlayer()
{
	GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Red, TEXT("YOU LOSE!"));

	if (ResultsWidgetObj)
	{
		// Show widget on screen
		ResultsWidgetObj->AddToViewport();

		// Optionally tell the widget it’s a loss
		//ResultsWidgetObj->SetLose(); // Assuming you implemented this in CodeResultsWidget

		if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
		{
			// Switch to UI-only input
			FInputModeUIOnly InputMode;
			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			InputMode.SetWidgetToFocus(ResultsWidgetObj->TakeWidget());

			PC->SetInputMode(InputMode);
			PC->bShowMouseCursor = true;
		}
	}

	// Null out player reference (if needed)
	CurrentPlayer = nullptr;
}
