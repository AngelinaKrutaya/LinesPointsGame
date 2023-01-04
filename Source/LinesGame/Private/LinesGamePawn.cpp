// Fill out your copyright notice in the Description page of Project Settings.
#include "LinesGamePawn.h"
#include "LinesGameElement.h"
#include "LinesGameElemLine.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "../LinesGameGameModeBase.h"
#include "DrawDebugHelpers.h"

// Sets default values
ALinesGamePawn::ALinesGamePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}


// Called when the game starts or when spawned
void ALinesGamePawn::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
}

// Called every frame
void ALinesGamePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TouchSetup();
}

// Called to bind functionality to input
void ALinesGamePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ALinesGamePawn::BeginTouch);
	PlayerInputComponent->BindTouch(IE_Released, this, &ALinesGamePawn::EndTouch);
}

void ALinesGamePawn::BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FHitResult Hit;
	bool bValid = PlayerController->GetHitResultUnderCursor(ECC_Visibility, true, Hit);
	if (bValid) {
		if (ALinesGameElement* ElementTouch = Cast<ALinesGameElement>(Hit.GetActor())) {
			Sphere = ElementTouch;
			Sphere->SetTouchLocation(Hit.Location);
			PlayVibration();
		}
	}
	bPressed = true;
}

void ALinesGamePawn::EndTouch(const ETouchIndex::Type FingerIndex,const  FVector Location)
{
	StopActionElem();
}

void ALinesGamePawn::TouchSetup()
{

	if (bPressed) {
		FHitResult Hit;
		bool bValidHit = PlayerController->GetHitResultUnderCursor(ECC_Visibility, true, Hit);
		if (bValidHit) {
			if (Line) {
				bool bValid = Line->CalcScore(Hit.Location);
				if (!bValid || Line->IsActorBeingDestroyed()) {
					StopActionElem();
				}
			}
			else if (ALinesGameElemLine* ElementTouch = Cast<ALinesGameElemLine>(Hit.GetActor())) {
				if (ElementTouch->StartFromBegin(Hit.Location)) { 
					Line = ElementTouch; 
					PlayVibration();
				}
			}

			if (Sphere) {
				if (Sphere->IsActorBeingDestroyed()) {
					StopActionElem();
				}
			}
		}
	}
}

void ALinesGamePawn::StopActionElem()
{
	bPressed = false;
	if (Line) {
		Line->Released();
		Line = nullptr;
	}
	if (Sphere) {
		Sphere->CalcScore();
		Sphere->Released();
		Sphere = nullptr;
	}
}

void ALinesGamePawn::PlayVibration()
{
	ALinesGameGameModeBase* GameMode = Cast<ALinesGameGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode->GetVibrationGame()) {
		PlayerController->PlayDynamicForceFeedback(0.3, 0.2, false, false, false, false);
	}
}


