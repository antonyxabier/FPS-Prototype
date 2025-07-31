// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class END2503AC_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()

public:
    // Set Health
    UFUNCTION(BlueprintCallable)
    void SetHealth(float p);

    //Set ammo
    UFUNCTION(BlueprintCallable)
    void SetAmmo(float Current, float Max);

    // Pure Function to Get Destination
    UFUNCTION(BlueprintPure)
    FVector GetDestination();

    // Override Tick for dynamic updates
    virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* CurrentAmmo;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* MaxAmmo;

protected:
    // Bindable Widgets
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    class UProgressBar* HealthBar;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD, meta = (BindWidget))
    UImage* Crosshair;

    // Linear Colors
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
    UMaterialInstanceDynamic* DynamicMaterial;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
    FName ColorName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
    FLinearColor SafeColor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
    FLinearColor DangerColor;

    virtual void NativeConstruct() override;
    void UpdateCrosshair();

private:
    FVector EndPoint;

    // Get Screen Position of Crosshair
    UFUNCTION(BlueprintCallable, Category = "HUD")
    FVector2D GetCrosshairScreenPosition();

	
};
