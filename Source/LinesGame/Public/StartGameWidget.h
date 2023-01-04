// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StartGameWidget.generated.h"

/**
 * 
 */
class UButton;

UCLASS()
class LINESGAME_API UStartGameWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
	UButton* ConfirmButton;

	UPROPERTY(meta = (BindWidget))
	UButton* RejectButton;

private:
	UFUNCTION()
	void OnConfirmStartGame();

	UFUNCTION()
	void OnRejectStartGame();

};
