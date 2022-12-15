// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CarWheel.h"
#include "WheeledVehicle.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "DriveToSurviveGameModeBase.h"
#include "Components/SpotLightComponent.h"
#include "Sound/SoundCue.h"
#include "BaseCar.generated.h"
class UWheeledVehicleMovementComponent4W;
/**
 * 
 */
UCLASS()
class DRIVETOSURVIVE_API ABaseCar : public AWheeledVehicle
{
	GENERATED_BODY()

	int BaseRate = 100000;
	float CarMess;
	UPROPERTY(EditAnywhere)
	UCameraComponent* ExternalCamera;
	UPROPERTY(EditAnywhere)
	UCameraComponent* InternalCamera;
	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere)
	UAudioComponent* Audio;
	bool bExternal = true;
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

	TArray<UCarWheel*> CarWheelsArray;
	FTimerHandle Timer;

	UPROPERTY(EditAnywhere)
	UMaterial* Material;

	UPROPERTY(EditAnywhere)
	USpotLightComponent* LeftPointLight;
	UPROPERTY(EditAnywhere)
	USpotLightComponent* RightPointLight;

	int Lable;
	
	void WearTyre();

	ADriveToSurviveGameModeBase* GameModeBase;
	bool (ADriveToSurviveGameModeBase::*CarRunable)();
	bool bStart;

	bool bUseLight;
	void TurnLight();
	
public:
	bool bCanUseDRS;
	bool bInDRSPlace;
	UPROPERTY(EditAnywhere)
	float MaxSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
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
	float GetGearChangeTime();
	UFUNCTION()
	virtual void OnOverlayBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                            const FHitResult& SweepResult);
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	           FVector NormalImpulse, const FHitResult& Hit);
	void SetSwitchGearTime(float Time);
	UFUNCTION()
	virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp,
		bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
	ABaseCar();
};
