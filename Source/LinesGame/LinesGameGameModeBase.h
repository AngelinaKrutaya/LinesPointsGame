// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LinesGamePlayerController.h"
#include "Engine/StaticMeshActor.h"
#include "LinesGamePlayerState.h"
#include "LinesGameGameStateBase.h"
#include "LinesGameLevel.h"
#include "LinesSaveGame.h"
#include "LinesGameGameModeBase.generated.h"
/**
 * 
 */
UENUM(BlueprintType)
enum class ELinesGameState :uint8
{
	MainMenu = 0,
	Settings,
	StartGame,
	Run,
	Pause,
	GameOver
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameStateChanged, ELinesGameState);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLevelOver, int32, FString);
DECLARE_MULTICAST_DELEGATE(FOnScoreChanged);


UCLASS()
class LINESGAME_API ALinesGameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ALinesGameGameModeBase();

	FOnGameStateChanged OnGameStateChanged;
	FOnLevelOver OnLevelOver;
	FOnScoreChanged OnScoreChanged;
	virtual void BeginPlay() override;
	void SetGameState(ELinesGameState State);
	void SpawnLevel();
	void GameOver(ELinesGameState State,const FString& Text);
	void SetCurrentLevel(const FName& Name) { CurrentLevelName =Name; }
	ALinesGamePlayerState* PlayerState;
	ALinesGameGameStateBase* GameStateClass;
	ALinesGameLevel* Level;


	UPROPERTY(BlueprintReadWrite, Category = "Score")
	FString SaveGameName;

	UPROPERTY(BlueprintReadOnly)
	ULinesSaveGame* SaveGameObj;

	UFUNCTION(BlueprintCallable, Category = "Score")
	void LoadGame();

	UFUNCTION(BlueprintCallable, Category = "Score")
	void SaveGame();

	bool GetVibrationUi() {
		return bVibrationUi;
	}

	bool GetVibrationGame() {
		return bVibrationGame;
	}

	void SoundUiChanged(bool bChecked);
	void SoundGameChanged(bool bChecked);
private:
	ELinesGameState GameState = ELinesGameState::MainMenu;
	FName CurrentLevelName;
	bool bVibrationUi = true;
	bool bVibrationGame = true;
	
};
