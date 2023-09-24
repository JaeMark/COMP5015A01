// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UMyGameInstance::SetInputMode(bool GameOnly) const {
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

void UMyGameInstance::StartGame()
{
	if (bIsPlaying) {
		ResumeGame();
	}
	else {
		LoadLevel();
	}
}

void UMyGameInstance::SetPlayingState(bool IsPlaying)
{
	bIsPlaying = IsPlaying;
}

void UMyGameInstance::LoadLevel()
{
	// Load level if game is not running
	if (GameLevel.IsNull()) {
		UE_LOG(LogTemp, Error, TEXT("No GameLevel set"));
		return;
	}

	bIsPlaying = true;

	UGameplayStatics::SetGamePaused(GetWorld(), false);
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, GameLevel);
}

void UMyGameInstance::ResumeGame()
{
	UGameplayStatics::SetGamePaused(GetWorld(), false);
}
