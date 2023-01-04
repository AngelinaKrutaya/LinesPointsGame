// Fill out your copyright notice in the Description page of Project Settings.

#include "PauseUserWidget.h"
#include "Components/Button.h"
#include "../LinesGameGameModeBase.h"

void UPauseUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (Continue) {
		Continue->OnClicked.AddDynamic(this, &UPauseUserWidget::OnContinue);
	}
	if (Back) {
		Back->OnClicked.AddDynamic(this, &UPauseUserWidget::OnBackToMenu);
	}
}

void UPauseUserWidget::OnBackToMenu()
{
	if (!GetWorld()){
		return;
	}

	ALinesGameGameModeBase* GameMode = Cast<ALinesGameGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode) {
		if (GameMode->GetVibrationUi()) {
			GetWorld()->GetFirstPlayerController()->PlayDynamicForceFeedback(0.3, 0.2, false, false, false, false);
		}
		GameMode->PlayerState->SetScore(0);
		GameMode->Level->DestroyAllActors();
		GameMode->ClearPause();
		GameMode->SetGameState(ELinesGameState::MainMenu);
		GameMode->SaveGame();
	}
}

void UPauseUserWidget::OnContinue()
{
	if (!GetWorld()) {
		return;
	}

	ALinesGameGameModeBase* GameMode = Cast<ALinesGameGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode) {
		if (GameMode->GetVibrationUi()) {
			GetWorld()->GetFirstPlayerController()->PlayDynamicForceFeedback(0.3, 0.2, false, false, false, false);
		}
		GameMode->ClearPause();
		GameMode->SetGameState(ELinesGameState::Run);
	}
}
