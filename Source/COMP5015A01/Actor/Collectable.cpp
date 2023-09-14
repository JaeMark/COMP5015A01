// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectable.h"

#include "Components/SphereComponent.h"

// Sets default values
ACollectable::ACollectable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collectable = CreateDefaultSubobject<UStaticMeshComponent>("CollectableMesh");
	Collectable->SetSimulatePhysics(true);
	Collectable->SetNotifyRigidBodyCollision(true);
	// Attach the cube to the default scene root
	RootComponent = Collectable;

	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("CollectorCollider"));
	Collider->SetupAttachment(Collectable);

}

// Called when the game starts or when spawned
void ACollectable::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACollectable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


