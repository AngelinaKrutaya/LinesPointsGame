// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LinesGameLevel.h"
#include "LinesGameElement.generated.h"

UCLASS()
class LINESGAME_API ALinesGameElement : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALinesGameElement();

	/** StaticMesh component for the clickable block */
	UPROPERTY(Category = Element, VisibleDefaultsOnly, BlueprintReadOnly)
	class UStaticMeshComponent* ElementMesh;

	UPROPERTY()
	class UMaterial* BaseMaterial;

	UPROPERTY()
	class UMaterialInstance* BlueMaterial;

	UFUNCTION(BlueprintCallable)
	void Released();

	UPROPERTY()
	class ALinesGameLevel* GameLevel;

	void CalcScore();
	void SetTouchLocation(const FVector& Point) {
		TouchLocation = Point;
	}

	FVector GetTouchLocation() {
		return TouchLocation;
	}
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
private:
	FVector TouchLocation;
};
