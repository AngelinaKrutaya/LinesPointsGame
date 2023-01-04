// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/KismetMathLibrary.h"
#include "LinesGamePlayerState.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE_OneParam(FOnScoreGameChanged, int32);

UCLASS()
class LINESGAME_API ALinesGamePlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	FOnScoreGameChanged OnScoreGameChanged;

	void CalcScoreLine(int32 Distance, int32 SplineKey);
	void CalcScoreSphere(int32 Distance);

	void SetStartPoint(int32 Key) {
		StartKey = Key;
		CurrentKey = Key;
	}
	void SetScore(const float Score);
private:
	int32 StartKey = 0;
	int32 CurrentKey = 0;
	int32 MaxScorePoint = 200;
	int32 MaxScoreSphere = 100;
};
