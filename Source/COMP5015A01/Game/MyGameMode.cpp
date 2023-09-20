// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"

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

void AMyGameMode::GameCompleted(bool PlayerWon) {
	if (DefaultGameCompleteWidget) {
		GameCompleteWidget = CreateWidget<UUserWidget>(GetWorld(), DefaultGameCompleteWidget);
		if (GameCompleteWidget) {
			GameCompleteWidget->AddToViewport();
			UTextBlock* LostOrComplete = Cast<UTextBlock>(
				GameCompleteWidget->GetWidgetFromName(TEXT("LostOrComplete"))
			);
			if (LostOrComplete) {
				const FText WinLossMessage = PlayerWon ? FText::FromString("You Won!") : FText::FromString("You Lost!");
				LostOrComplete->SetText(WinLossMessage);
			}
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