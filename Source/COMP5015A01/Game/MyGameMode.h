// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateScore, float, NewScore);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateTimer, FString, NewTime);

UCLASS()
class COMP5015A01_API AMyGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyGameMode();

protected:
	FTimerHandle CountdownTimer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG")
	TSubclassOf<UUserWidget> DefaultGameCompleteWidget;

	UPROPERTY()
	UUserWidget* GameCompleteWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG")
	TSubclassOf<UUserWidget> DefaultScoreWidget;

	UPROPERTY()
	UUserWidget* ScoreWidget;

	UPROPERTY()
	float CurrentScore = 0.0f;

	UPROPERTY()
	int32 CountdownTime = 120;

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FOnUpdateScore OnUpdateScore;

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FOnUpdateTimer OnUpdateTimer;

public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void GameCompleted();
	void UpdateTimer();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateScore(float DeltaScore);
};
