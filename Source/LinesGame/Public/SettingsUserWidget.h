// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../LinesGameGameModeBase.h"
#include "SettingsUserWidget.generated.h"

/**
 * 
 */
class UCheckBox;
class UButton;


UCLASS()
class LINESGAME_API USettingsUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
	UCheckBox* VibrationUI;

	UPROPERTY(meta = (BindWidget))
	UCheckBox* VibrationGame;

	UPROPERTY(meta = (BindWidget))
	UButton* Back;

	UFUNCTION()
	void OnSoundsUIChanged(bool bIsChecked);

	UFUNCTION()
	void OnSoundsGameChanged(bool bIsChecked);

	UFUNCTION()
	void OnBack();
private:
	ALinesGameGameModeBase* GameMode;
};
