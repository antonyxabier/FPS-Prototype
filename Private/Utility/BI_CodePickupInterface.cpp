// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/BI_CodePickupInterface.h"

// Add default functionality here for any IBI_CodePickupInterface functions that are not pure virtual.

bool IBI_CodePickupInterface::CanPickupHealth_Implementation()
{
	return false;
}

bool IBI_CodePickupInterface::CanPickupAmmo_Implementation()
{
	return false;
}
