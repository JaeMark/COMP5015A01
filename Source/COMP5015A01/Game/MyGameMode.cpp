// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include <Kismet/GameplayStatics.h>

AMyGameMode::AMyGameMode() {
	// Set this pawn to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AMyGameMode::BeginPlay() {
	if (DefaultStartWidget) {
		StartWidget = CreateWidget<UUserWidget>(GetWorld(), DefaultStartWidget);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("%s"), *FString("DefaultStartWidget has not been set."));
	}

	SetInputMode(true);

	if (DefaultGameHUD) {
		GameHUD = CreateWidget<UUserWidget>(GetWorld(), DefaultGameHUD);
		GameHUD->AddToViewport();
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("%s"), *FString("DefaultScoreWidget has not been set."));
	}

	OnUpdateScore.Broadcast(CurrentScore);

	GetWorldTimerManager().SetTimer(CountdownTimer, this, &AMyGameMode::UpdateTimer, 1.0f, true);
}

void AMyGameMode::UpdateTimer()
{
	// Convert seconds to minutes and seconds
	int32 Minutes = CountdownTime / 60;
	int32 Seconds = CountdownTime % 60;

	// Format the time as "MM:SS"
	FString TimerText = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);

	// Update your UI with the TimerText
	OnUpdateTimer.Broadcast(TimerText);

	if (CountdownTime == 0) {
		GetWorldTimerManager().ClearTimer(CountdownTimer);
		GameCompleted();
	}

	CountdownTime--;
}

void AMyGameMode::SetInputMode(bool GameOnly) const {
	const UWorld* World = GetWorld();
	if (!World) {
		UE_LOG(LogTemp, Warning, TEXT("%s"), *FString("Cannot access world"));
		return;
	}
	if (APlayerController* const Controller = World->GetFirstPlayerController()) {
		if (GameOnly) {
			const FInputModeGameOnly InputMode;
			Controller->SetInputMode(InputMode);
		}
		else {
			const FInputModeUIOnly InputMode;
			Controller->SetInputMode(InputMode);
		}

		Controller->bShowMouseCursor = !GameOnly;
	}
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

	// Pause game
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}

void AMyGameMode::UpdateScore_Implementation(float DeltaScore) {
	CurrentScore += DeltaScore;
	OnUpdateScore.Broadcast(CurrentScore);
}

void AMyGameMode::ReplayGame() {
	if (GameLevel.IsNull()){
		UE_LOG(LogTemp, Error, TEXT("No GameLevel set"));
		return;
	}

	UGameplayStatics::SetGamePaused(GetWorld(), false);
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, GameLevel);
}

void AMyGameMode::TogglePauseGame(){
	bPauseGame = !bPauseGame;

	if (bPauseGame) {
		StartWidget->AddToViewport();
	}
	else {
		StartWidget->RemoveFromViewport();
	}

	SetInputMode(!bPauseGame);
	UGameplayStatics::SetGamePaused(GetWorld(), bPauseGame);
}