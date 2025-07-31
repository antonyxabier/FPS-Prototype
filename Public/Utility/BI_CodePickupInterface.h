// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BI_CodePickupInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBI_CodePickupInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class END2503AC_API IBI_CodePickupInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	UFUNCTION(BlueprintNativeEvent, Category = "Pickup")
	bool CanPickupHealth();
	virtual bool CanPickupHealth_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "Pickup")
	bool CanPickupAmmo();
	virtual bool CanPickupAmmo_Implementation();

};
