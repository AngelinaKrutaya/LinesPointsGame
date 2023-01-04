// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LinesGameGameStateBase.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.generated.h"

/**
 * 
 */

class UButton;
class UScrollBox;
class ULevelIconWidget;

UCLASS()
class LINESGAME_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
	UScrollBox* LevelIconBox;

	UPROPERTY(meta = (BindWidget))
	UButton* Settings;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> LevelIconWidget;

	UFUNCTION()
	void OnSettings();

	virtual void NativeOnInitialized() override;

private:
	UPROPERTY()
	TArray<ULevelIconWidget*> LevelIconWidgets;

	void InitLevelIcons();
	void OnLevelSelect(const FLevelData& Data);

};
