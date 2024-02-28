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

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	/** Camera variables */

	// Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<class UCameraComponent> Camera;

	// Name of the socket to which camera is attached
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
	FName CameraSocketName;

	float BaseTurnRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Camera)
	float HipTurnRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Camera)
	float AimingTurnRate;

protected:
	/** Weapon variables and functions */

	// The weapons spawned by default
	UPROPERTY(EditDefaultsOnly, Category = Configurations)
	TArray<TSubclassOf<class AWeapon>> DefaultWeapons;

public:

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Replicated, Category = State)
	TArray<TObjectPtr<class AWeapon>> Weapons;

protected:
	/** Variables and functions related to input */

	// Mapping context
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputMappingContext> MappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	TObjectPtr<class UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	TObjectPtr<class UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	TObjectPtr<class UInputAction> FireAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	TObjectPtr<class UInputAction> AimAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	TObjectPtr<class UInputAction> ReloadAction;

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

	FORCEINLINE TObjectPtr<class UCameraComponent> GetFollowCamera() const;

};
