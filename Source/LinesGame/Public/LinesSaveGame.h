// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "LinesGameGameStateBase.h"
#include "LinesSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class LINESGAME_API ULinesSaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	TArray<FLevelData> SavedDataLevels;
};
