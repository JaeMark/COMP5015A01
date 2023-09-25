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

	GetWorldTimerManager().SetTimer(SpawnerTimer, this, &ACollectablesSpawner::SpawnCollectable, SpawnInterval, true);

}

// Called every frame
void ACollectablesSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACollectablesSpawner::SpawnCollectable()
{
    if (CollectablesToSpawn.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("No collectables available to spawn!"));
        return;
    }

    const FVector SpawnLocation = FVector(GetActorLocation().X,
        FMath::RandRange(SpawnVolume->GetComponentLocation().Y - SpawnVolume->GetScaledBoxExtent().Y,
        SpawnVolume->GetComponentLocation().Y + SpawnVolume->GetScaledBoxExtent().Y),
        GetActorLocation().Z);

    // Generate a random index to select a random collectable from the array
    int32 RandomIndex = FMath::RandRange(0, CollectablesToSpawn.Num() - 1);

    // Spawn the random collectable
    ACollectable* NewCollectable = GetWorld()->SpawnActor<ACollectable>(CollectablesToSpawn[RandomIndex], SpawnLocation, FRotator::ZeroRotator);
}
