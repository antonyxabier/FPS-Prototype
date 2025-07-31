// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CodeButtonWithText.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnClickedEvent);

/**
 * 
 */
UCLASS()
class END2503AC_API UCodeButtonWithText : public UUserWidget
{
	GENERATED_BODY()

	UCodeButtonWithText(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* BackgroundButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* Information;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)

	FText Info;

	UFUNCTION()
	void HandleClickButton();

public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = Delegate)

	FOnClickedEvent OnClickedEvent;

	
};
