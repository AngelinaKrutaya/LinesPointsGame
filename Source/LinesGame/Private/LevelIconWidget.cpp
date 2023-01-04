// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelIconWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "../LinesGameGameModeBase.h"
#include "LinesGameGameStateBase.h"

void ULevelIconWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	LevelButton->OnClicked.AddDynamic(this, &ULevelIconWidget::OnLevelIconClicked);
}


void ULevelIconWidget::SetLevelData(const FLevelData& Data)
{
	LevelData = Data;
	if (LevelName) {
		LevelName->SetText(FText::FromName(Data.LevelName));
	}
	const auto GameMode = Cast<ALinesGameGameModeBase>(GetWorld()->GetAuthGameMode());
	int32 Score = GameMode->GameStateClass->GetScoreLevel(LevelData.LevelName);
	if (BestScore) {
		BestScore->SetText(FText::FromString(FString::FromInt(Score)));
	}
	if (GameMode) {
		GameMode->OnScoreChanged.AddUObject(this, &ULevelIconWidget::OnScoreChanged);
	}
}

void ULevelIconWidget::OnLevelIconClicked()
{
	OnLevelSelected.Broadcast(LevelData);
}

void ULevelIconWidget::OnScoreChanged()
{
	const auto GameMode = Cast<ALinesGameGameModeBase>(GetWorld()->GetAuthGameMode());
	int32 Score = GameMode->GameStateClass->GetScoreLevel(LevelData.LevelName);
	if (BestScore) {
		BestScore->SetText(FText::FromString(FString::FromInt(Score)));
	}
}