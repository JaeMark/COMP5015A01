// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"

AMyGameMode::AMyGameMode()
{
	// Set this pawn to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AMyGameMode::BeginPlay() {

	if (DefaultScoreWidget) {
		ScoreWidget = CreateWidget<UUserWidget>(GetWorld(), DefaultScoreWidget);
		ScoreWidget->AddToViewport();
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("%s"), *FString("DefaultScoreWidget has not been set."));
	}

	OnUpdateScore.Broadcast(CurrentScore);
}

// Called every frame
void AMyGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyGameMode::GameCompleted() {
	if (DefaultGameCompleteWidget) {
		GameCompleteWidget = CreateWidget<UUserWidget>(GetWorld(), DefaultGameCompleteWidget);
		if (GameCompleteWidget) {
			GameCompleteWidget->AddToViewport();
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("%s"), *FString("DefaultGameCompleteWidget has not been set."));
	}
}

void AMyGameMode::UpdateScore_Implementation(float DeltaScore) {
	CurrentScore += DeltaScore;
	OnUpdateScore.Broadcast(CurrentScore);
}