// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/CodeGamePlayerController.h"

ACodeGamePlayerController::ACodeGamePlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACodeGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
}
