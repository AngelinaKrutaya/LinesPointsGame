// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ElementsDataTable.generated.h"

/**
 * 
 */


UENUM(BlueprintType)
enum class EDataType :uint8
{
	Sphere,
	Line
};

USTRUCT()
struct FTableInfo:public FTableRowBase {
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	TArray<FVector> Coord;

	UPROPERTY(EditAnywhere)
	EDataType ElementType = EDataType::Sphere;

	UPROPERTY(EditAnywhere)
	float SpawnTime=0.f;

	UPROPERTY(EditAnywhere)
	float LifeTime=0.f;
};
