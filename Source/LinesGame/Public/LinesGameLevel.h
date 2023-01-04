// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ElementsDataTable.h"
#include "LinesGamePlayerState.h"
#include "LinesGameLevel.generated.h"

UCLASS()
class LINESGAME_API ALinesGameLevel : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ALinesGameLevel();

	UPROPERTY(EditAnywhere)
	TMap<FName,UDataTable*> ElementsData;

	void NextElement();
	void SpawnElements();
	void SetLevel(FName& LevelName);
	void DestroyAllActors();
	void AddClickedElement() {
		ClickedElement += 1;
	}
	void SetPlayerState(ALinesGamePlayerState* PlayerState) {
		PlayerStateClass = PlayerState;
	}

	static bool Compare(const FTableInfo& Time1, const FTableInfo& Time2)
	{
		return Time1.SpawnTime <= Time2.SpawnTime;
	}

	virtual void Tick(float DeltaTime) override;
	class ALinesGamePlayerState* PlayerStateClass;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	int32 SpawnedElement = 0;
	TArray<FTableInfo*> AllRows;
	int32 ClickedElement = 0;
	float CurrentTime = 0.f;
	FTimerHandle TimerHandle;
	TArray<AActor*> Elements;
	bool GameOver = false;
};
