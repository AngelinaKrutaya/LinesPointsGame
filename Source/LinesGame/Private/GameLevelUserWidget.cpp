// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLevelUserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "../LinesGameGameModeBase.h"
#include "LinesGamePlayerState.h"

void UGameLevelUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	ALinesGameGameModeBase* GameMode = Cast<ALinesGameGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode) {
		GameMode->PlayerState->OnScoreGameChanged.AddUObject(this, &UGameLevelUserWidget::OnScoreChanged);
	}
	if (PauseButton) {
		PauseButton->OnClicked.AddDynamic(this, &UGameLevelUserWidget::OnPause);
	}
}


void UGameLevelUserWidget::OnScoreChanged(int32 ScoreData)
{
	if (Score) {
		Score->SetText(FText::FromString(FString::FromInt(ScoreData)));
	}
}

void UGameLevelUserWidget::OnPause()
{
	if (!GetWorld()) {
		return;
	}

	ALinesGameGameModeBase* GameMode = Cast<ALinesGameGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode) {
		if (GameMode->GetVibrationUi()) {
			GetWorld()->GetFirstPlayerController()->PlayDynamicForceFeedback(0.3, 0.2, false, false, false, false);
		}
		GameMode->SetPause(GetWorld()->GetFirstPlayerController());
		GameMode->SetGameState(ELinesGameState::Pause);
	}
}
