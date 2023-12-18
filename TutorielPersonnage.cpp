/**
 * Fichier TutorielPersonnage.cpp
 * Auteur: Merlin Tourigny
 *
 * Date: 20 d�cembre 2023
 *
 * Fichier qui s'occupe des mouvements et animations du joueur
 */
#include "TutorielPersonnage.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

ATutorielPersonnage::ATutorielPersonnage()
{
    // Activer la mise � jour � chaque frame
    PrimaryActorTick.bCanEverTick = true;

    // Configurer la taille de la capsule de collision
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    // Configurer le mouvement du personnage
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

    // Param�tres de saut
    GetCharacterMovement()->JumpZVelocity = 700.f;
    GetCharacterMovement()->AirControl = 0.35f;
    GetCharacterMovement()->MaxWalkSpeed = 500.f;
    GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
    GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
    GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

    // Cr�er un CameraBoom
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 400.0f;
    CameraBoom->bUsePawnControlRotation = true;

    // Cr�er une cam�ra qui suit le joueur
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;
}

void ATutorielPersonnage::BeginPlay()
{
    Super::BeginPlay();

    // Ajouter les inputs au joueur
    if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(DefaultMappingContext, 0);
        }
    }
}

void ATutorielPersonnage::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ATutorielPersonnage::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    // S'occupe des actions du joueur
    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        // Sauter
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

        // D�placement
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATutorielPersonnage::Move);

        // Regarder
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATutorielPersonnage::Look);
    }
    else
    {
        UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' �chec de trouver un composant Enhanced Input ! Ce mod�le est con�u pour utiliser le syst�me Enhanced Input. Si vous avez l'intention d'utiliser l'ancien syst�me, vous devrez mettre � jour ce fichier C++."), *GetNameSafe(this));
    }
}

void ATutorielPersonnage::Move(const FInputActionValue& Value)
{
    // R�cup�rer le vecteur de d�placement
    FVector2D MovementVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        // Trouver la direction vers l'avant
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // Obtenir le vecteur vers l'avant
        const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

        // Obtenir le vecteur vers la droite
        const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        // Effectuer le mouvement
        AddMovementInput(ForwardDirection, MovementVector.Y);
        AddMovementInput(RightDirection, MovementVector.X);
    }
}

void ATutorielPersonnage::Look(const FInputActionValue& Value)
{
    // R�cup�rer le vecteur de la cameraBoom
    FVector2D LookAxisVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        // lui met les nouvelles coordonn�es
        AddControllerYawInput(LookAxisVector.X);
        AddControllerPitchInput(LookAxisVector.Y);
    }
}
