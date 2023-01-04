// Fill out your copyright notice in the Description page of Project Settings.
#include "LinesGameGameStateBase.h"
#include "LinesGameInstance.h"

void ALinesGameGameStateBase::SetScoreLevel(int32 Score)
{
	for (FLevelData& Levels : DataLevels) {
		if (CurrentLevel.LevelName == Levels.LevelName) {
			if (Score >= Levels.ScoreLevel)
			{
				Levels.ScoreLevel = Score;
			}
		}
	}
}

int32 ALinesGameGameStateBase::GetScoreLevel(FName LevelName)
{
	for (FLevelData& Levels : DataLevels) {
		if (Levels.LevelName == LevelName) {
			return Levels.ScoreLevel;
		}
	}
	return 0;
}
