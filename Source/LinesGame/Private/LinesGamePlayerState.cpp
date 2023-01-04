// Fill out your copyright notice in the Description page of Project Settings.


#include "LinesGamePlayerState.h"


void ALinesGamePlayerState::CalcScoreLine(int32 Distance, int32 SplineKey)
{
	if (CurrentKey != SplineKey) {
		CurrentKey = SplineKey;
		if (Distance > 0) {
			SetScore(GetScore() + ((MaxScorePoint * FMath::Abs(StartKey - CurrentKey)) / Distance));
			OnScoreGameChanged.Broadcast(GetScore());
		}
	}
}

void ALinesGamePlayerState::CalcScoreSphere(int32 Distance)
{
	if (Distance > 0) {
		SetScore(GetScore() + (MaxScoreSphere / Distance));
		OnScoreGameChanged.Broadcast(GetScore());
	}
}

void ALinesGamePlayerState::SetScore(const float ScoreData)
{
	Super::SetScore(ScoreData);
	OnScoreGameChanged.Broadcast(ScoreData);
}
