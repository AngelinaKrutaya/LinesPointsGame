// Copyright Epic Games, Inc. All Rights Reserved.

#include "LinesGameGameModeBase.h"
#include "LinesGamePawn.h"
#include "LinesGameHUD.h"
#include "LinesGamePlayerController.h"
#include "SettingsUserWidget.h"
#include "Kismet/GameplayStatics.h"


ALinesGameGameModeBase::ALinesGameGameModeBase() {
	DefaultPawnClass = ALinesGamePawn::StaticClass();
	PlayerControllerClass = ALinesGamePlayerController::StaticClass();
	HUDClass = ALinesGameHUD::StaticClass();
	PlayerStateClass = ALinesGamePlayerState::StaticClass();
	SaveGameName = "SaveGame";
}


void ALinesGameGameModeBase::SetGameState(ELinesGameState State)
{
	if (GameState == State) {
		return;
	}

	GameState = State;
	OnGameStateChanged.Broadcast(GameState);
}

void ALinesGameGameModeBase::SpawnLevel()
{
	Level->SetLevel(CurrentLevelName);
	Level->SetPlayerState(PlayerState);
	Level->SpawnElements();
}

void ALinesGameGameModeBase::LoadGame()
{
	USaveGame* LoadedGame = UGameplayStatics::LoadGameFromSlot(SaveGameName, 0);
	SaveGameObj = Cast<ULinesSaveGame>(LoadedGame);
	if (!SaveGameObj)
	{
		SaveGameObj = Cast<ULinesSaveGame>(UGameplayStatics::CreateSaveGameObject(ULinesSaveGame::StaticClass()));
		const bool IsSaved = UGameplayStatics::SaveGameToSlot(SaveGameObj, SaveGameName, 0);
	}
	else {
		for (int i = 0; i < SaveGameObj->SavedDataLevels.Num(); ++i) {
			GameStateClass->DataLevels[i] = SaveGameObj->SavedDataLevels[i];
		}
	}
}

void ALinesGameGameModeBase::SaveGame()
{
	SaveGameObj->SavedDataLevels = GameStateClass->DataLevels;
	const bool IsSaved = UGameplayStatics::SaveGameToSlot(SaveGameObj, SaveGameName, 0);
}

void ALinesGameGameModeBase::GameOver(ELinesGameState State, const FString& Text)
{
	GameStateClass->SetScoreLevel(PlayerState->GetScore());
	OnLevelOver.Broadcast(PlayerState->GetScore(), Text);
	PlayerState->SetScore(0);
	ALinesGamePlayerController* PlayerController = Cast<ALinesGamePlayerController>(GetWorld()->GetFirstPlayerController());
	OnScoreChanged.Broadcast();
	SetGameState(State);
	SaveGame();
}

void ALinesGameGameModeBase::SoundUiChanged(bool bChecked)
{
	bVibrationUi = bChecked;
}

void ALinesGameGameModeBase::SoundGameChanged(bool bChecked)
{
	bVibrationGame = bChecked;
}


void ALinesGameGameModeBase::BeginPlay()
{
	ALinesGamePlayerController* PlayerController = Cast<ALinesGamePlayerController>(GetWorld()->GetFirstPlayerController());
	if (PlayerController) {
		PlayerState = Cast<ALinesGamePlayerState>(PlayerController->PlayerState);
		GameStateClass = Cast<ALinesGameGameStateBase>(GetWorld()->GetGameState());
	}
	AActor* FoundActor;
	FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), ALinesGameLevel::StaticClass());
	Level = Cast<ALinesGameLevel>(FoundActor);
	LoadGame();
}
