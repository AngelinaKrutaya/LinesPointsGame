// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseUserWidget.generated.h"

/**
 * 
 */

class UButton;
class UTextBlock;

UCLASS()
class LINESGAME_API UPauseUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(meta = (BindWidget))
	UButton* Back;

	UPROPERTY(meta = (BindWidget))
	UButton* Continue;

	virtual void NativeOnInitialized() override;

	UFUNCTION()
	void OnBackToMenu();

	UFUNCTION()
	void OnContinue();
};
