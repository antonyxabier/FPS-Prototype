// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/CodeMainMenu.h"
#include "Widgets/CodeButtonWithText.h"
#include "Utility/CodeGameInstance.h"

void UCodeMainMenu::NativeConstruct()
{
    Super::NativeConstruct();

    if (StartGameButton)
    {
        StartGameButton->OnClickedEvent.AddDynamic(this, &UCodeMainMenu::HandleStartClicked);
    }

    if (QuitGameButton)
    {
        QuitGameButton->OnClickedEvent.AddDynamic(this, &UCodeMainMenu::HandleQuitClicked);
    }
}

void UCodeMainMenu::HandleStartClicked()
{
    if (UCodeGameInstance* GameInstance = Cast<UCodeGameInstance>(GetGameInstance()))
    {
        GameInstance->LoadFirstLevel();
    }
}

void UCodeMainMenu::HandleQuitClicked()
{
    if (UCodeGameInstance* GameInstance = Cast<UCodeGameInstance>(GetGameInstance()))
    {
        GameInstance->ExitTheGame();
    }
}