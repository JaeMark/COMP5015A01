// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Collectable.generated.h"

// Forward Declarations:
class USphereComponent;

UCLASS()
class COMP5015A01_API ACollectable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollectable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// ASSET COMPONENTS
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Setup)
		USphereComponent* Collider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Setup)
		UStaticMeshComponent* Collectable;

	UFUNCTION(BlueprintImplementableEvent)
		void UpdateScore(float DeltaScore) const;
};
