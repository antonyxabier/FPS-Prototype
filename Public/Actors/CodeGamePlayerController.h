// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CodeGamePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class END2503AC_API ACodeGamePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ACodeGamePlayerController();

protected:
	virtual void BeginPlay() override;
	
};
