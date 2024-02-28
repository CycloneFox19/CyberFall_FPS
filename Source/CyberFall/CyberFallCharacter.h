// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "CyberFallCharacter.generated.h"

UCLASS()
class CYBERFALL_API ACyberFallCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACyberFallCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	/** Camera variables */

	// Camera boom
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<class USpringArmComponent> CameraBoom;

	// Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<class UCameraComponent> FollowCamera;

	// Name of the socket to which camera is attached
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
	FName CameraSocketName;

	// Local offset of camera boom
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	FVector CameraBoomOffset;

	float BaseTurnRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Camera)
	float HipTurnRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Camera)
	float AimingTurnRate;

protected:
	/** Variables and functions related to input */

	// Mapping context
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputMappingContext> MappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	TObjectPtr<UInputAction> FireAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	TObjectPtr<UInputAction> AimAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	TObjectPtr<UInputAction> ReloadAction;

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

protected:
	/** Variables and functions related to movement */
	
	// Movement speed
	float Speed;

	// Movement speed of walking
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float WalkSpeed;

public:
	/** Public getters */
	FORCEINLINE TObjectPtr<USpringArmComponent> GetCameraBoom() const;

	FORCEINLINE TObjectPtr<UCameraComponent> GetFollowCamera() const;

};
