// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExampleFunctions.generated.h"

UCLASS()
class END2503AC_API AExampleFunctions : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExampleFunctions();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//this lets you call functions from blueprint
	UFUNCTION(BlueprintCallable)
	void BlueprintCallable();

	//Blueprint implementable event - declare in c++, define in blueprint
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void BlueprintImplementableEvent();

	//BlueprintNativeEvent - declare in c++, define in c++ but with _Implementation, can override in Blueprint
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void BlueprintNativeEvent(); // in c++ call using this
	virtual void BlueprintNativeEvent_Implementation(); //in c++ override using this

	//Pure function
	UFUNCTION(BlueprintCallable)
	float PureFunction() const;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
