// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverUserWidget.generated.h"

/**
 * 
 */

class UButton;
class UTextBlock;

UCLASS()
class LINESGAME_API UGameOverUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(meta = (BindWidget))
	UButton* Back;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Score;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* OverText;


	virtual void NativeOnInitialized() override;

	UFUNCTION()
	void OnBackToMenu();

	void OnLevelOver(int32 ScoreData,FString Text);
};
