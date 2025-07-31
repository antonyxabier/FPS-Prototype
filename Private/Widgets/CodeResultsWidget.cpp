// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/CodeResultsWidget.h"
#include "Utility/CodeGameInstance.h"
#include "Widgets/CodeButtonWithText.h"
#include "Components/VerticalBox.h"
#include "Components/WidgetSwitcher.h"

void UCodeResultsWidget::SetWin()
{
    if (ButtonArea)
    {
        ButtonArea->SetVisibility(ESlateVisibility::Hidden);
        if (ResultSwitch)
        {
            ResultSwitch->SetActiveWidgetIndex(1);
            //Set Timer to go to the main menu
            FTimerHandle TimerHandle;
            GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UCodeResultsWidget::LoadMainMenu, TimeToMenu, false);

        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("ERROR: We need the ResultSwitch!"));
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "ERROR: We need the ResultSwitch!");

        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("ERROR: We need the ButtonArea!"));
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "ERROR: We need the ButtonArea!");
    }
}

void UCodeResultsWidget::NativeConstruct()
{
    TimeToMenu = 2.0f;

    if (UGameInstance* GI = GetGameInstance())
    {
        GameInstance = Cast<UCodeGameInstance>(GI);
        if (!GameInstance)
        {
            UE_LOG(LogTemp, Error, TEXT("ERROR: We need the UCodeGameInstance!"));
        }
    }
    if (MenuButton)
    {
        MenuButton->OnClickedEvent.AddDynamic(GameInstance, &UCodeGameInstance::LoadMainMenu);
    }

    if (RestartButton && GameInstance)
    {
        RestartButton->OnClickedEvent.AddDynamic(GameInstance, &UCodeGameInstance::LoadCurrentLevel);
    }
}

void UCodeResultsWidget::LoadMainMenu()
{
    MenuButton->OnClickedEvent.Broadcast();
}
