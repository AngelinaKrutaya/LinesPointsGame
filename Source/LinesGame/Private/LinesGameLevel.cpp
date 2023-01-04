// Fill out your copyright notice in the Description page of Project Settings.


#include "LinesGameLevel.h"
#include "LinesGameElement.h"
#include "LinesGameElemLine.h"
#include "Kismet/GameplayStatics.h"
#include "Containers/Array.h"
#include "../LinesGameGameModeBase.h"
#include "Containers/IndirectArray.h"


ALinesGameLevel::ALinesGameLevel()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
}

void ALinesGameLevel::SpawnElements()
{
	if (AllRows[SpawnedElement]->SpawnTime - CurrentTime == 0) {
		NextElement();
	}
	else {
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ALinesGameLevel::NextElement, AllRows[SpawnedElement]->SpawnTime - CurrentTime, false);
		CurrentTime = AllRows[SpawnedElement]->SpawnTime;
	}
}

void ALinesGameLevel::SetLevel(FName& LevelName)
{
	Elements.Empty();
	ClickedElement = 0;
	ElementsData[LevelName]->GetAllRows<FTableInfo>(TEXT("Info"), AllRows);
	AllRows.Sort(ALinesGameLevel::Compare);
	CurrentTime = AllRows[SpawnedElement]->SpawnTime;
}

void ALinesGameLevel::Tick(float DeltaTime)
{
	if (SpawnedElement - ClickedElement > 3) {
		DestroyAllActors();
		ALinesGameGameModeBase* GameMode = Cast<ALinesGameGameModeBase>(GetWorld()->GetAuthGameMode());
		GameMode->PlayerState->SetScore(0);
		GameMode->GameOver(ELinesGameState::GameOver, "You lose");
	}else if (AllRows.Num() && SpawnedElement == AllRows.Num()) {
		GameOver = true;
		for (auto Iter = Elements.CreateIterator(); Iter; ++Iter) {
			if (!(*Iter)->IsActorBeingDestroyed()) {
				GameOver = false;
			}
		}
		if (GameOver) {
			ALinesGameGameModeBase* GameMode = Cast<ALinesGameGameModeBase>(GetWorld()->GetAuthGameMode());
			GameMode->GameOver(ELinesGameState::GameOver, "You win");
			GameOver = false;
			SpawnedElement = 0;
			AllRows.Empty();
		}
	}
}


void ALinesGameLevel::DestroyAllActors()
{
	SpawnedElement = 0;
	AllRows.Empty();
	for (auto Iter = Elements.CreateIterator(); Iter; ++ Iter) {
		if (!(*Iter)->IsActorBeingDestroyed()) {
			(*Iter)->Destroy();
		}
	}
}

// Called when the game starts or when spawned
void ALinesGameLevel::BeginPlay()
{
	Super::BeginPlay();
}

void ALinesGameLevel::NextElement() {
	GetWorldTimerManager().ClearTimer(TimerHandle);

	if (SpawnedElement < AllRows.Num()) {
		if (AllRows[SpawnedElement]->ElementType == EDataType::Sphere) {
			for (FVector Coord : AllRows[SpawnedElement]->Coord) {
				ALinesGameElement* NewElement = GetWorld()->SpawnActor<ALinesGameElement>(FVector(Coord.X, Coord.Y, 0.f) + GetActorLocation(), GetActorRotation());
				NewElement->SetLifeSpan(AllRows[SpawnedElement]->LifeTime);
				NewElement->GameLevel = this;
				Elements.Add(NewElement);
			}
		}
		if (AllRows[SpawnedElement]->ElementType == EDataType::Line) {
			const FTransform ActorTransform = FTransform(GetActorLocation());
			ALinesGameElemLine* NewElement = GetWorld()->SpawnActorDeferred<ALinesGameElemLine>(ALinesGameElemLine::StaticClass(), ActorTransform);
			NewElement->SetSplinePoints(AllRows[SpawnedElement]->Coord);
			NewElement->SetLifeSpan(AllRows[SpawnedElement]->LifeTime);
			NewElement->GameLevel = this;
			UGameplayStatics::FinishSpawningActor(NewElement, ActorTransform);
			Elements.Add(NewElement);
		}
		SpawnedElement++;
		if (SpawnedElement < AllRows.Num()) {
			SpawnElements();
		}
	}
}


