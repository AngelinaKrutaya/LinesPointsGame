// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LinesGameGameStateBase.h"
#include "LevelIconWidget.generated.h"

/**
 * 
 */

class UButton;
class UTextBlock;

UCLASS()
class LINESGAME_API ULevelIconWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	FOnLevelSelected OnLevelSelected;
	void SetLevelData(const FLevelData& Data);
	FLevelData LevelData;

	UPROPERTY(meta = (BindWidget))
	UButton* LevelButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* LevelName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* BestScore;

	void OnScoreChanged();
	virtual void NativeOnInitialized() override;
private:

	UFUNCTION()
	void OnLevelIconClicked();
};
