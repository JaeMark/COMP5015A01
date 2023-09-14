// Fill out your copyright notice in the Description page of Project Settings.

#include "CollectablesSpawner.h"
#include "Collectable.h"
#include "Components/BoxComponent.h"

// Sets default values
ACollectablesSpawner::ACollectablesSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnVolume = CreateDefaultSubobject<UBoxComponent>("SpawnVolume");
	RootComponent = SpawnVolume;
}

// Called when the game starts or when spawned
void ACollectablesSpawner::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(SpawnerTimer, [this]() { SpawnCollectable(); }, 2.0f, true);
}

// Called every frame
void ACollectablesSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACollectablesSpawner::SpawnCollectable()
{
    const FVector SpawnLocation = FVector(GetActorLocation().X,
										  FMath::RandRange(SpawnVolume->GetComponentLocation().Y - SpawnVolume->GetScaledBoxExtent().Y,
										  SpawnVolume->GetComponentLocation().Y + SpawnVolume->GetScaledBoxExtent().Y),
									      GetActorLocation().Z);

    // Spawn the collectable
    ACollectable* NewCollectable = GetWorld()->SpawnActor<ACollectable>(CollectablesToSpawn, SpawnLocation, FRotator::ZeroRotator);
}
