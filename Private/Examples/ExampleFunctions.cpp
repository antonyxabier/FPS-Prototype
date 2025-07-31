// Fill out your copyright notice in the Description page of Project Settings.


#include "Examples/ExampleFunctions.h"
#include "../END2503AC.h"

// Sets default values
AExampleFunctions::AExampleFunctions()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AExampleFunctions::BeginPlay()
{
	Super::BeginPlay();
	
}

void AExampleFunctions::BlueprintCallable()
{
	UE_LOG(Game, Log, TEXT("In C++ BlueprintCallable"));
}

//void AExampleFunctions::BlueprintImplementableEvent()
//{
	//UE_LOG(Game, Log, TEXT("BlueprintImplementableEvent"));
//}

void AExampleFunctions::BlueprintNativeEvent_Implementation()
{
	UE_LOG(Game, Log, TEXT("In C++ BlueprintNativeEvent"));
}

float AExampleFunctions::PureFunction() const
{
	return 3.14f;
}

// Called every frame
void AExampleFunctions::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

