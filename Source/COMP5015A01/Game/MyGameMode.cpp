// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameMode.h"

void AMyGameMode::BeginPlay() {

}

void AMyGameMode::UpdateScore_Implementation(float DeltaScore) {
	CurrentScore += DeltaScore;
	OnUpdateScore.Broadcast(CurrentScore);
}