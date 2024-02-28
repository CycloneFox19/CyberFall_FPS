// Fill out your copyright notice in the Description page of Project Settings.


#include "CyberFallCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ACyberFallCharacter::ACyberFallCharacter()
	: CameraSocketName(TEXT("VB head_root"))
	, BaseTurnRate(1.f)
	, HipTurnRate(1.f)
	, AimingTurnRate(0.6f)
	, WalkSpeed(600.f)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetMesh(), CameraSocketName);
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->TargetArmLength = 0.f;
	CameraBoom->SetRelativeLocation(CameraBoomOffset);

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	BaseTurnRate = HipTurnRate;

	bUseControllerRotationRoll = false;
	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;

	Speed = WalkSpeed;
}

// Called when the game starts or when spawned
void ACyberFallCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (TObjectPtr<APlayerController> PlayerController = Cast<APlayerController>(GetController()))
	{
		if (TObjectPtr<UEnhancedInputLocalPlayerSubsystem> Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(MappingContext, 0);
		}
	}
	
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

// Called every frame
void ACyberFallCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACyberFallCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACyberFallCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACyberFallCharacter::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
	}
}

void ACyberFallCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (GetController())
	{
		const FRotator YawRotation = { 0.f, Controller->GetControlRotation().Yaw, 0.f };
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y * Speed);
		AddMovementInput(RightDirection, MovementVector.X * Speed);
	}
}

void ACyberFallCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookRotationValue = Value.Get<FVector2D>();

	if (GetController())
	{
		AddControllerYawInput(LookRotationValue.X * BaseTurnRate);
		AddControllerPitchInput(LookRotationValue.Y * BaseTurnRate);
	}
}

TObjectPtr<USpringArmComponent> ACyberFallCharacter::GetCameraBoom() const
{
	return CameraBoom;
}

TObjectPtr<UCameraComponent> ACyberFallCharacter::GetFollowCamera() const
{
	return FollowCamera;
}

