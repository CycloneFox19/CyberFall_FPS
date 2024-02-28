// Fill out your copyright notice in the Description page of Project Settings.


#include "CyberFallAnimInstance.h"
#include "CyberFallCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

UCyberFallAnimInstance::UCyberFallAnimInstance()
	: SpineRotationOffset(FRotator(0.f, 0.f, 0.f))
	, Speed(0.f)
	, bIsInAir(false)
	, bIsAccelerating(false)
	, MovementOffsetYaw(0.f)
{
}

void UCyberFallAnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	if (!CyberFallCharacter)
	{
		CyberFallCharacter = Cast<ACyberFallCharacter>(TryGetPawnOwner());
	}

	if (CyberFallCharacter)
	{
		Speed = CyberFallCharacter->GetVelocity().Size();
		bIsInAir = CyberFallCharacter->GetCharacterMovement()->IsFalling();
		bIsAccelerating = CyberFallCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f;

		const FRotator AimRotation = CyberFallCharacter->GetBaseAimRotation();
		const FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(CyberFallCharacter->GetVelocity());
		MovementOffsetYaw = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation).Yaw;

		const float UpperAngle = 360.f - CyberFallCharacter->GetControlRotation().Pitch;
		const float LowerAngle = -CyberFallCharacter->GetControlRotation().Pitch;
		SpineRotationOffset.Roll = (CyberFallCharacter->GetControlRotation().Pitch > 180.f) ? UpperAngle : LowerAngle;
		SpineRotationOffset.Roll *= 0.2f; // We rotate five spine bones by this rotator, therefore we need to divide it by 5.f
	}
}

void UCyberFallAnimInstance::NativeInitializeAnimation()
{
	CyberFallCharacter = Cast<ACyberFallCharacter>(TryGetPawnOwner());
}
