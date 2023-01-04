// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "LinesGamePawn.generated.h"

UCLASS()
class LINESGAME_API ALinesGamePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ALinesGamePawn();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location) ;
	void EndTouch(const ETouchIndex::Type FingerIndex,const FVector Location);
private:
	bool bPressed = false;
	void TouchSetup();
	void StopActionElem();
	void PlayVibration();

	class ALinesGameElemLine* Line;
	class ALinesGameElement* Sphere;
	APlayerController* PlayerController;
};
