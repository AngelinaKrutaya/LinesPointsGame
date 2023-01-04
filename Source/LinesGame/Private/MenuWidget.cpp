// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"
#include "Components/ScrollBox.h"
#include "Components/Button.h"
#include "../LinesGameGameModeBase.h"
#include "LinesGameGameStateBase.h"
#include "LevelIconWidget.h"

void UMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	InitLevelIcons();
	if (Settings) {
		Settings->OnClicked.AddDynamic(this, &UMenuWidget::OnSettings);
	}
}

void UMenuWidget::InitLevelIcons()
{
	ALinesGameGameStateBase* GameState = Cast<ALinesGameGameStateBase>(GetWorld()->GetGameState());
	if (!GameState) { 
		return;
	}
	if (GameState->DataLevels.Num() == 0) {
		return;
	}
	for (FLevelData& LevelData : GameState->DataLevels)
	{
		ULevelIconWidget* LevelIcon = CreateWidget<ULevelIconWidget>(GetWorld(), LevelIconWidget);
		if (!LevelIcon) {
			continue;
		}
		LevelIcon->SetLevelData(LevelData);
		LevelIcon->OnLevelSelected.AddUObject(this, &UMenuWidget::OnLevelSelect);
		LevelIconBox->AddChild(LevelIcon);
		LevelIconWidgets.Add(LevelIcon);
	}
}

void UMenuWidget::OnLevelSelect(const FLevelData& Data)
{
	ALinesGameGameStateBase* GameState = Cast<ALinesGameGameStateBase>(GetWorld()->GetGameState());
	if (!GameState) {
		return;
	}

	GameState->SetLevel(Data);
	ALinesGameGameModeBase* GameMode = Cast<ALinesGameGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode) {
		if (GameMode->GetVibrationUi()) {
			GetWorld()->GetFirstPlayerController()->PlayDynamicForceFeedback(0.3, 0.2, false, false, false, false);
		}
		GameMode->SetGameState(ELinesGameState::StartGame);
		GameMode->SetCurrentLevel(Data.LevelName);
	}
}

void UMenuWidget::OnSettings()
{
	if (!GetWorld()) {
		return;
	}

	ALinesGameGameModeBase* GameMode = Cast<ALinesGameGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode) {
		if (GameMode->GetVibrationUi()) {
			GetWorld()->GetFirstPlayerController()->PlayDynamicForceFeedback(0.3, 0.2, false, false, false, false);
		}
		GameMode->SetGameState(ELinesGameState::Settings);
	}
}

