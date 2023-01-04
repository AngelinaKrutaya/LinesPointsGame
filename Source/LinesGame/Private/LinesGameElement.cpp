// Fill out your copyright notice in the Description page of Project Settings.


#include "LinesGameElement.h"

// Sets default values
ALinesGameElement::ALinesGameElement()
{
	PrimaryActorTick.bCanEverTick = true;
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> SphereMesh;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> BaseMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> BlueMaterial;
		FConstructorStatics()
			: SphereMesh(TEXT("/Game/Meshes/Sphere.Sphere"))
			, BaseMaterial(TEXT("/Game/Meshes/BaseMaterial.BaseMaterial"))
			, BlueMaterial(TEXT("/Game/Meshes/BlueMaterial.BlueMaterial"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));

	// Create static mesh component
	ElementMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Element"));
	ElementMesh->SetStaticMesh(ConstructorStatics.SphereMesh.Get());
	ElementMesh->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	ElementMesh->SetMaterial(0, ConstructorStatics.BlueMaterial.Get());
	ElementMesh->SetupAttachment(RootComponent);
	ElementMesh->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
	BaseMaterial = ConstructorStatics.BaseMaterial.Get();
	BlueMaterial = ConstructorStatics.BlueMaterial.Get();

}

void ALinesGameElement::CalcScore()
{   
	int32 Distance = FVector::Distance(ElementMesh->GetComponentLocation(), TouchLocation);
	GameLevel->PlayerStateClass->CalcScoreSphere(Distance);
}

// Called when the game starts or when spawned
void ALinesGameElement::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALinesGameElement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ALinesGameElement::Released()
{
	GameLevel->AddClickedElement();
	GetWorld()->DestroyActor(this);
}


