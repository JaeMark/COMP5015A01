#include "PlayerCharacter.h"

#include "Collectable.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/Engine.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/GameplayStatics.h"
#include "COMP5015A01/Game/MyGameMode.h"
#include "COMP5015A01/Game/MyGameInstance.h"

using UEILPS = UEnhancedInputLocalPlayerSubsystem;
using UEIC = UEnhancedInputComponent;

// Sets default values
APlayerCharacter::APlayerCharacter()
{
    // Set this pawn to call Tick() every frame. You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // Create a cube mesh component
    Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
    Cube->SetSimulatePhysics(true);
    Cube->SetNotifyRigidBodyCollision(true);
    // Attach the cube to the default scene root
    RootComponent = Cube;

    // Lock cube rotation
    Cube->BodyInstance.bLockXRotation = true;
    Cube->BodyInstance.bLockYRotation = true;
    Cube->BodyInstance.bLockZRotation = true;
    // Lock cube x translation
    Cube->BodyInstance.bLockXTranslation = true;

    CollectorCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("CollectorCollider"));
    CollectorCollider->SetupAttachment(Cube);

    // Create movement component
    MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>("Movement");
    MovementComponent->UpdatedComponent = Cube;

    // Add an initial impulse to make the ball bounce
    const FVector InitialImpulse = FVector(0.0f, 0.0f, 1000.0f); // Adjust the Z component to control the initial bounce height
    Cube->AddImpulse(InitialImpulse, NAME_None, true);

    GameModeRef = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
    GameInstanceRef = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (const APlayerController* PlayerController = Cast<APlayerController>(GetController())) {
        const ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
        UEILPS* SubSystem = ULocalPlayer::GetSubsystem<UEILPS>(LocalPlayer);
        if (SubSystem) {
            SubSystem->AddMappingContext(InputMappingContext, 0);
        }
    }

    if (CollectorCollider) {
        CollectorCollider->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnBeginOverlap);
    }
}

void APlayerCharacter::PlayerDied() {
    if (GameModeRef) {
        GameModeRef->GameCompleted();
    }
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
    if (GetActorLocation().Z < KillZThreshold) {
        PlayerDied();
    }
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    if (UEIC* EnhancedInputComponent = CastChecked<UEIC>(PlayerInputComponent)) {
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::MoveHorizontally);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Jump);
        EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Triggered, this, &APlayerCharacter::PauseGame);
    }
}

void APlayerCharacter::Jump(const FInputActionValue& Value)
{
    // Apply a boost force to the cube
    if (Value.Get<float>() > 0.0f) {
        MovementComponent->AddInputVector(FVector(0.0f, 0.0f, 1.0f) * BoostForce);
    }
}

void APlayerCharacter::PauseGame()
{
    if (GameModeRef) {
        GameInstanceRef->PauseGame();
    }
}

void APlayerCharacter::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor->IsA(ACollectable::StaticClass())) {
        //OtherActor->Destroy();
    }
}

void APlayerCharacter::MoveHorizontally(const FInputActionValue& Value) 
{
    // Move the sphere horizontally based on input
    const float MovementAxis = Value.Get<float>();
    const FVector CubeForce = FVector(0.0f, MovementAxis * SideForce, 0.0f);
    Cube->AddForce(CubeForce, NAME_None, true);
}


