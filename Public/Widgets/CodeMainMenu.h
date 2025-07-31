// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CodeMainMenu.generated.h"

class UCodeButtonWithText;
class UCodeGameInstance;

/**
 * 
 */
UCLASS()
class END2503AC_API UCodeMainMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UCodeButtonWithText* StartGameButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UCodeButtonWithText* QuitGameButton;

private:
	UFUNCTION()
	void HandleStartClicked();

	UFUNCTION()
	void HandleQuitClicked();
	
};
