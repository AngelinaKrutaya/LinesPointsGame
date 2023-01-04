// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameLevelUserWidget.generated.h"

/**
 * 
 */
class UButton;
class UTextBlock;

UCLASS()
class LINESGAME_API UGameLevelUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(meta = (BindWidget))
	UButton* PauseButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Score;

	virtual void NativeOnInitialized() override;

	void OnScoreChanged(int32 Score);
	
	UFUNCTION()
	void OnPause();
};
