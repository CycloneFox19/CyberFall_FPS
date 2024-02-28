// Fill out your copyright notice in the Description page of Project Settings.


#include "CyberFallAnimInstance.h"
#include "CyberFallCharacter.h"

UCyberFallAnimInstance::UCyberFallAnimInstance()
	: SpineRotationOffset(FRotator(0.f, 0.f, 0.f))
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
