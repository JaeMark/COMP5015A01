// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CollectablesSpawner.generated.h"


// Forward Declarations:
class UBoxComponent;
class ACollectable;

UCLASS()
class COMP5015A01_API ACollectablesSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollectablesSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	FTimerHandle SpawnerTimer;

	// ASSET COMPONENTS
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Setup)
	UBoxComponent* SpawnVolume;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ACollectable> CollectablesToSpawn;

	void SpawnCollectable();
};


