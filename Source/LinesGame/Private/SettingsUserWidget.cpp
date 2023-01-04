// Fill out your copyright notice in the Description page of Project Settings.
#include "SettingsUserWidget.h"
#include "Components/CheckBox.h"
#include "Components/Button.h"

void USettingsUserWidget::NativeOnInitialized() {
	Super::NativeOnInitialized();

	if (VibrationUI) {
		VibrationUI->OnCheckStateChanged.AddDynamic(this, &USettingsUserWidget::OnSoundsUIChanged);
	}

	if (VibrationGame) {
		VibrationGame->OnCheckStateChanged.AddDynamic(this, &USettingsUserWidget::OnSoundsGameChanged);
	}

	if (Back) {
		Back->OnClicked.AddDynamic(this, &USettingsUserWidget::OnBack);
	}

	if (GetWorld()) {
		GameMode = Cast<ALinesGameGameModeBase>(GetWorld()->GetAuthGameMode());
	}

}

void USettingsUserWidget::OnSoundsUIChanged(bool bIsChecked)
{
	if (GameMode) {
		GameMode->SoundUiChanged(bIsChecked);
	}
}

void USettingsUserWidget::OnSoundsGameChanged(bool bIsChecked)
{
	if (GameMode) {
		GameMode->SoundGameChanged(bIsChecked);
	}
}

void USettingsUserWidget::OnBack()
{
	if (GameMode) {
		if (GameMode->GetVibrationUi()) {
			GetWorld()->GetFirstPlayerController()->PlayDynamicForceFeedback(0.3, 0.2, false, false, false, false);
		}
		GameMode->SetGameState(ELinesGameState::MainMenu);
	}
}
