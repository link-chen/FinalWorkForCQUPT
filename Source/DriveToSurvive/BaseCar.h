// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehicle.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "DriveToSurviveGameModeBase.h"
#include "Sound/SoundCue.h"
#include "BaseCar.generated.h"
/**
 * 
 */
UCLASS()
class DRIVETOSURVIVE_API ABaseCar : public AWheeledVehicle
{
	GENERATED_BODY()
	
	int BaseRate=100000;
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
	float ERSRate;
	bool bUseERS;
	bool bERSCanOpen;
	FTimerHandle ERSTimeCount;
	UPROPERTY(EditAnywhere)
	float ERSTickTime;
	UPROPERTY(EditAnywhere)
	float DownForceRate;
	UPROPERTY(EditAnywhere)
	float ReChargeRate;
	
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
	void QuitGame();
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	ADriveToSurviveGameModeBase* GameModeBase;
	bool (ADriveToSurviveGameModeBase:: *CarRunable)();
	bool bStart;
public:
	bool bCanUseDRS;
	bool bInDRSPlace;
	UPROPERTY(EditAnywhere)
	float MaxSpeed;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	float MaxElectronicPower;
	UPROPERTY(BlueprintReadOnly)
	float ElectronicPower;
	UPROPERTY(EditAnywhere)
	float ElectronicCost;
	FVector LastLocation;
	FRotator ReBornRotator;
	UPROPERTY(BlueprintReadOnly)
	bool bCanCarRun;
	void UseDRS();
	void DisableDRS();
	void UseERS();
	void ERS();
	void ReSetTransform();
	UFUNCTION(BlueprintImplementableEvent)
	void LightOut();
	float GetERSRate();
	void SetERSRate(float Value);
	float GetDownForceRate();
	void SetDownForceRate(float Value);
	float GetReChargeRate();
	void SetReChargeRate(float Value);
	float GetGeerChangeTime();
	void SetGeerChangeTime(float Value);
	ABaseCar();
};
