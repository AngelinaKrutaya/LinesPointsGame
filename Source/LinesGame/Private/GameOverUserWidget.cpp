// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverUserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "../LinesGameGameModeBase.h"

void UGameOverUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	ALinesGameGameModeBase* GameMode = Cast<ALinesGameGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode) {
		GameMode->OnLevelOver.AddUObject(this, &UGameOverUserWidget::OnLevelOver);
	}
	if (Back) {
		Back->OnClicked.AddDynamic(this, &UGameOverUserWidget::OnBackToMenu);
	}
}

void UGameOverUserWidget::OnBackToMenu()
{
	if (!GetWorld()) {
		return;
	}

	ALinesGameGameModeBase* GameMode = Cast<ALinesGameGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode) {
		if (GameMode->GetVibrationUi()) {
			GetWorld()->GetFirstPlayerController()->PlayDynamicForceFeedback(0.3, 0.2, false, false, false, false);
		}
		GameMode->SetGameState(ELinesGameState::MainMenu);
	}
}

void UGameOverUserWidget::OnLevelOver(int32 ScoreData, FString Text)
{
	if (Score) {
		Score->SetText(FText::FromString(FString::FromInt(ScoreData)));
	}
	if (OverText) {
		OverText->SetText(FText::FromString(Text));
	}
}
