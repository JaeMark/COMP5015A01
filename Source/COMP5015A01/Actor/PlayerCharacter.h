// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "PlayerCharacter.generated.h"

// Forward Declarations:
class UInputMappingContext;
class UInputAction;
class UBoxComponent;
class USpringArmComponent;
class UCameraComponent;
class UFloatingPawnMovement;
class AMyGameMode;
class UMyGameInstance;

UCLASS()
class COMP5015A01_API APlayerCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// ENHANCED INPUT SYSTEM
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	// In your class declaration (PlayerCharacter.h):
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* PauseAction;

	UPROPERTY(BlueprintReadOnly)
	UMyGameInstance* GameInstanceRef;

	void MoveHorizontally(const FInputActionValue& Value);
	void Jump(const FInputActionValue& Value);
	void PauseGame();

	// ASSET COMPONENTS
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Setup)
	UBoxComponent* CollectorCollider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Setup)
	UStaticMeshComponent* Cube;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Setup)
	UFloatingPawnMovement* MovementComponent;

	// MOVEMENT VARIABLES
	UPROPERTY(EditAnywhere, Category = "Movement");
	float SideForce = 1800.0f;

	UPROPERTY(EditAnywhere, Category = "Movement");
	float BoostForce = 1800.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AMyGameMode* GameModeRef;

	UFUNCTION() // The names of these functions don't matter, but the signature does.
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
