// Fill out your copyright notice in the Description page of Project Settings.

#include "LinesGameElemLine.h"
#include "../LinesGameGameModeBase.h"


// Sets default values
ALinesGameElemLine::ALinesGameElemLine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SplineComponent = CreateDefaultSubobject<USplineComponent>("Spline");
	SplineComponent->SetupAttachment(RootComponent);
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> SphereMesh;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> LineMesh;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> BaseMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> HighlightMaterial;
		FConstructorStatics()
			: SphereMesh(TEXT("/Game/Meshes/Sphere.Sphere"))
			, LineMesh(TEXT("/Game/Meshes/Line_SM.Line_SM"))
			, BaseMaterial(TEXT("/Game/Meshes/LineMaterial.LineMaterial"))
			, HighlightMaterial(TEXT("/Game/Meshes/BaseMaterial.BaseMaterial"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	StaticMesh = ConstructorStatics.LineMesh.Get();
	Material = ConstructorStatics.HighlightMaterial.Get();
	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Element"));
	SphereMesh->SetStaticMesh(ConstructorStatics.SphereMesh.Get());
	SphereMesh->SetMaterial(0, ConstructorStatics.BaseMaterial.Get());
	SphereMesh->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	SphereMesh->SetupAttachment(SplineComponent);

	SphereMesh2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Element2"));
	SphereMesh2->SetStaticMesh(ConstructorStatics.SphereMesh.Get());
	SphereMesh2->SetMaterial(0, ConstructorStatics.BaseMaterial.Get());
	SphereMesh2->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	SphereMesh2->SetupAttachment(SplineComponent);
}

void ALinesGameElemLine::OnConstruction(const FTransform& Transform)
{
	SplineComponent->SetSplinePoints(SplinePoints, ESplineCoordinateSpace::World);
	const int32 SplinePointsElem = SplineComponent->GetNumberOfSplinePoints();
	for (int SplineCount = 0; SplineCount < (SplinePointsElem - 1); SplineCount++) {
		SplineMesh = NewObject<USplineMeshComponent>(this, USplineMeshComponent::StaticClass());
		SplineMesh->SetStaticMesh(StaticMesh);
		SplineMesh->SetForwardAxis(ESplineMeshAxis::Z, true);
		SplineMesh->RegisterComponentWithWorld(GetWorld());
		SplineMesh->CreationMethod = EComponentCreationMethod::UserConstructionScript;
		SplineMesh->SetMobility(EComponentMobility::Movable);
		SplineMesh->AttachToComponent(SplineComponent, FAttachmentTransformRules::KeepWorldTransform);
		const FVector StartPoint = SplineComponent->GetLocationAtSplinePoint(SplineCount, ESplineCoordinateSpace::Type::World);
		const FVector StartTangent = SplineComponent->GetTangentAtSplinePoint(SplineCount, ESplineCoordinateSpace::Type::World);
		const FVector EndPoint = SplineComponent->GetLocationAtSplinePoint(SplineCount + 1, ESplineCoordinateSpace::Type::World);
		const FVector EndTangent = SplineComponent->GetTangentAtSplinePoint(SplineCount + 1, ESplineCoordinateSpace::Type::World);
		SplineMesh->SetStartAndEnd(StartPoint, StartTangent, EndPoint, EndTangent, true);
	}
}

// Called when the game starts or when spawned
void ALinesGameElemLine::BeginPlay()
{
	Super::BeginPlay();
	SphereMesh->SetWorldLocation(SplineComponent->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World));
	SphereMesh2->SetWorldLocation(SplineComponent->GetLocationAtSplinePoint(SplineComponent->GetNumberOfSplinePoints(), ESplineCoordinateSpace::World));
}


void ALinesGameElemLine::Released() {
	GameLevel->AddClickedElement();
	GetWorld()->DestroyActor(this);
}

bool ALinesGameElemLine::StartFromBegin(const FVector& Point)
{
	FVector FirstSplinePoint = SplineComponent->GetLocationAtSplinePoint(0,ESplineCoordinateSpace::World);
	FVector LastSplinePoint = SplineComponent->GetLocationAtSplinePoint(SplineComponent->GetNumberOfSplinePoints(), ESplineCoordinateSpace::World);
	if (FVector::Distance(Point, FirstSplinePoint) < 30.f) {
		BeginKey = 0;
		CurrentKey = BeginKey;
		GameLevel->PlayerStateClass->SetStartPoint(BeginKey);
		return true;
	}
	else if (FVector::Distance(Point, LastSplinePoint) < 30.f) {
		BeginKey = SplineComponent->GetNumberOfSplinePoints();
		CurrentKey = BeginKey;
		GameLevel->PlayerStateClass->SetStartPoint(BeginKey);
		return true;
	}
	else {
		return false;
	}
}

int32 ALinesGameElemLine::GetDistanceToSpline(const FVector& Point)
{
	FVector Location = SplineComponent->FindLocationClosestToWorldLocation(Point,ESplineCoordinateSpace::World);
	int32 Distance = FVector::Distance(Location, Point);
	if (BeginKey == 0) {
		SphereMesh->SetWorldLocation(Location);
		SphereMesh->SetMaterial(0, Material);
	}
	else {
		SphereMesh2->SetWorldLocation(Location);
		SphereMesh2->SetMaterial(0, Material);
	}
	return Distance;
}

int32 ALinesGameElemLine::GetSplineKeyClosestToLocation(const FVector& Point)
{
	int32 Key = SplineComponent->FindInputKeyClosestToWorldLocation(Point);
	return Key;
}

bool ALinesGameElemLine::CalcScore(const FVector& Point)
{
	int32 Distance = GetDistanceToSpline(Point);
	int32 Key = GetSplineKeyClosestToLocation(Point);
	if (Distance > 500) {
		return false;
	}

	if (BeginKey == 0) {
		if (CurrentKey > Key) { 
			return false; 
		}
	}
	else {
		if (CurrentKey < Key) {
			return false;
		}
	}

	GameLevel->PlayerStateClass->CalcScoreLine(Distance, Key);
	CurrentKey = Key;
	return true;
}


