// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "LinesGameGameStateBase.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ELevelName :uint8
{
	Level1,
	Level2,
	Level3
};

USTRUCT(BlueprintType)
struct FLevelData {
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "LevelData")
	FName LevelName = "Level1";

	UPROPERTY(EditDefaultsOnly, Category = "LevelData")
	int32 ScoreLevel = 0;
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnLevelSelected, const FLevelData&);

UCLASS()
class LINESGAME_API ALinesGameGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	TArray<FLevelData> DataLevels;

	void SetLevel(const FLevelData& Data) { CurrentLevel = Data; }
	void SetScoreLevel(int32 Score);
	int32 GetScoreLevel(FName LevelName);
private:
	FLevelData CurrentLevel;
};
