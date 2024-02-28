// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CyberFallAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class CYBERFALL_API UCyberFallAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	UCyberFallAnimInstance();

	UFUNCTION(BlueprintCallable)
	void UpdateAnimationProperties(float DeltaTime);

	// Called when game starts
	virtual void NativeInitializeAnimation() override;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	TObjectPtr<class ACyberFallCharacter> CyberFallCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	FRotator SpineRotationOffset;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	bool bIsInAir;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	bool bIsAccelerating;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	float MovementOffsetYaw;
	
};
