// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectable.h"

#include "PlayerCharacter.h"
#include "Components/SphereComponent.h"

// Sets default values
ACollectable::ACollectable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(Root);

	Collectable = CreateDefaultSubobject<UStaticMeshComponent>("CollectableMesh");
	Collectable->SetSimulatePhysics(true);
	Collectable->SetNotifyRigidBodyCollision(true);
	Collectable->SetupAttachment(Root);

	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("CollectorCollider"));
	Collider->SetupAttachment(Collectable);

	if (Collider) {
		Collider->OnComponentBeginOverlap.AddDynamic(this, &ACollectable::OnBeginOverlap);
	}
}

// Called when the game starts or when spawned
void ACollectable::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(LifetimeTimer, this, &ACollectable::DestroyActor, Lifetime, false);
}

// Called every frame
void ACollectable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACollectable::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (OtherActor && OtherActor->IsA(APlayerCharacter::StaticClass())) 
	{
		UpdateScore(PickupValue);
		Destroy();
	} 
}

void ACollectable::DestroyActor()
{
	Destroy();
}


