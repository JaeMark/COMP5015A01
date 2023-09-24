// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class COMP5015A01_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	bool bPauseGame = false;

	UPROPERTY()
	bool bIsPlaying = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UWorld> GameLevel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG")
	TSubclassOf<UUserWidget> DefaultStartWidget;

	UPROPERTY()
	UUserWidget* StartWidget;

public:
	virtual void Init() override;

	UFUNCTION(BlueprintCallable, Category = "Input Mode")
	void SetInputMode(bool GameOnly) const;

	UFUNCTION(BlueprintCallable, Category = "Game")
	void StartGame();

	UFUNCTION()
	void SetPlayingState(bool IsPlaying);

protected:
	void ResumeGame();
	void LoadLevel();
};
