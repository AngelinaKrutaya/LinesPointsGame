// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "LinesGameLevel.h"
#include "LinesGameElemLine.generated.h"



UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LINESGAME_API ALinesGameElemLine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALinesGameElemLine();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	TArray<FVector> SplinePoints;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Spline")
	USplineComponent* SplineComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	USplineMeshComponent* SplineMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Spline")
	UStaticMesh* StaticMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Spline")
	class UStaticMeshComponent* SphereMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Spline")
	class UStaticMeshComponent* SphereMesh2;

	UPROPERTY()
	class UMaterial* BaseMaterial;

	UPROPERTY()
	class ALinesGameLevel* GameLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	UMaterial* Material;

	virtual void OnConstruction(const FTransform& Transform) override;
	void SetSplinePoints(TArray<FVector> SplinePoints_) { SplinePoints = SplinePoints_; }

	UFUNCTION()
	void Released();

	bool StartFromBegin(const FVector& Point);
	int32 GetDistanceToSpline(const FVector& Point);
	int32 GetSplineKeyClosestToLocation(const FVector& Point);
	bool CalcScore(const FVector& Point);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	int32 BeginKey = 0;
	int32 CurrentKey = 0;
};
