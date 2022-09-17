// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehicle.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Sound/SoundCue.h"
#include "BaseCar.generated.h"

/**
 * 
 */
UCLASS()
class DRIVETOSURVIVE_API ABaseCar : public AWheeledVehicle
{
	GENERATED_BODY()

	
	UPROPERTY(EditAnywhere)
	UCameraComponent* ExternalCamera;
	UPROPERTY(EditAnywhere)
	UCameraComponent* InternalCamera;
	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere)
	UAudioComponent* Audio;
	bool bExternal=true;
	UPROPERTY(EditAnywhere)
	bool bIsmanual;
	bool bAddForce;
	float CurrentSpeed;
	UPROPERTY(EditAnywhere)
	float ElectronicPower;
	
	UPROPERTY(EditAnywhere)
	TArray<USoundCue*> SoundArray;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Brake();
	void CancleBrake();
	void PlayEngineSound();
	void ChangeCamera();
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
public:
	bool bCanUseDRS;
	bool bInDRSPlace;
	UPROPERTY(EditAnywhere)
	float MaxSpeed;
	void UseDRS();
	void DisableDRS();
	void UseERS();
	void CancleERS();
	ABaseCar();
};
