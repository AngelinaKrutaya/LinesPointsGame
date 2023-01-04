// Fill out your copyright notice in the Description page of Project Settings.

#include "LinesGameHUD.h"
#include "Blueprint/UserWidget.h"

void ALinesGameHUD::BeginPlay() {
	GameWidgets.Add(ELinesGameState::MainMenu, CreateWidget<UUserWidget>(GetWorld(), MenuWidget));
	GameWidgets.Add(ELinesGameState::Settings, CreateWidget<UUserWidget>(GetWorld(), SettingsWidget));
	GameWidgets.Add(ELinesGameState::StartGame, CreateWidget<UUserWidget>(GetWorld(), StartGameWidget));
	GameWidgets.Add(ELinesGameState::Run, CreateWidget<UUserWidget>(GetWorld(), BaseGameWidget));
	GameWidgets.Add(ELinesGameState::Pause, CreateWidget<UUserWidget>(GetWorld(), PauseWidget));
	GameWidgets.Add(ELinesGameState::GameOver, CreateWidget<UUserWidget>(GetWorld(), GameOverUserWidget));

	for (auto& GameWidget: GameWidgets) {
		if (!GameWidget.Value) return;

		GameWidget.Value->AddToViewport();
		GameWidget.Value->SetVisibility(ESlateVisibility::Hidden);
	}
	OnGameStateChanged(ELinesGameState::MainMenu);

	if (GetWorld()) {
		ALinesGameGameModeBase* GameMode = Cast<ALinesGameGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode) {
			GameMode->OnGameStateChanged.AddUObject(this, &ALinesGameHUD::OnGameStateChanged);
		}
	}

}
void ALinesGameHUD::OnGameStateChanged(ELinesGameState State)
{
	if (CurrentWidget && State!= ELinesGameState::StartGame)
		CurrentWidget->SetVisibility(ESlateVisibility::Hidden);

	if(State == ELinesGameState::Run)
		GameWidgets[ELinesGameState::MainMenu]->SetVisibility(ESlateVisibility::Hidden);

	if (GameWidgets.Contains(State)) 
		CurrentWidget = GameWidgets[State];

	if(CurrentWidget)
		CurrentWidget->SetVisibility(ESlateVisibility::Visible);
}
