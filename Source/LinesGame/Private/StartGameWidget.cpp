// Fill out your copyright notice in the Description page of Project Settings.


#include "StartGameWidget.h"
#include "Components/Button.h"
#include "../LinesGameGameModeBase.h"

void UStartGameWidget::NativeOnInitialized() {
	Super::NativeOnInitialized();

	ConfirmButton->OnClicked.AddDynamic(this, &UStartGameWidget::OnConfirmStartGame);
	RejectButton->OnClicked.AddDynamic(this, &UStartGameWidget::OnRejectStartGame);
}

void UStartGameWidget::OnConfirmStartGame()
{
	if (!GetWorld()) {
		return;
	}

	ALinesGameGameModeBase* GameMode = Cast<ALinesGameGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode) {
		GameMode->SetGameState(ELinesGameState::Run);
		GameMode->SpawnLevel();
	}
}

void UStartGameWidget::OnRejectStartGame()
{
	if (!GetWorld()) {
		return;
	}

	ALinesGameGameModeBase* GameMode = Cast<ALinesGameGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode) {
		GameMode->SetGameState(ELinesGameState::MainMenu);
	}
}
