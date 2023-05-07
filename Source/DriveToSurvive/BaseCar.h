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
#include "PlayerCharater.h"
#include "WheeledVehicleMovementComponent4W.h"
#include "BaseCar.generated.h"

class  PHYSXVEHICLES_API UCarTransData:public UWheeledVehicleMovementComponent4W
{
	
	int Weight;
public:
	UCarTransData()
	{
		
	}
	void UpdateCarEngineSetup(const FVehicleEngineData& NewEngineSetup)
	{
		UpdateEngineSetup(NewEngineSetup);
	}
	void UpdateCarDifferentialSetup(const FVehicleDifferential4WData& NewDifferentialSetup)
	{
		UpdateDifferentialSetup(NewDifferentialSetup);
	}
	void TransmissionReset(const FVehicleTransmissionData& NewGearSetup)
	{
		UpdateTransmissionSetup(NewGearSetup);
	}
};
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
	float BrakeBackRate;
	UPROPERTY(EditAnywhere)
	float TurboStart;

	UPROPERTY(EditAnywhere)
	float StartWorkRate;

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

	float GetInputRate();

	TArray<UCarWheel*> CarWheelsArray;
	FTimerHandle Timer;

	FTimerHandle TimerForChange;

	UPROPERTY(EditAnywhere)
	UMaterial* CrashedMaterial;
	UPROPERTY(EditAnywhere)
	UMaterial* CarWheelMaterial;

	UPROPERTY(EditAnywhere)
	TArray<FName> CarWheelBoneName;

	bool bDraw;

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


	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Weight;
	

	UPROPERTY(EditAnywhere)
	FRuntimeFloatCurve ERSCurve;
	FRuntimeFloatCurve BaseCurve;

	float Drag;
	float DownForce;
	UPROPERTY(EditAnywhere)
	float Square;
	UPROPERTY(EditAnywhere)
	float H;
	UPROPERTY(EditAnywhere)
	float DeltaSquare;
	UPROPERTY(EditAnywhere)
	float DeltaH;
	UPROPERTY(EditAnywhere)
	float Cd;
	float AirRow;
	UPROPERTY(EditAnywhere)
	float BaseOutPut;
	
public:
	bool bCanUseDRS;
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
	float GetERSRate();
	void SetERSRate(float Value);
	float GetDownForceRate();
	void SetDownForceRate(float Value);
	float GetReChargeRate();
	void SetReChargeRate(float Value);
	float GetGearChangeTime();
	UFUNCTION(BlueprintImplementableEvent)
	void PausedGame();
	UFUNCTION(BlueprintCallable)
	void ShowRunning();
	UFUNCTION(BlueprintCallable)
	void HideRunning();
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
	UFUNCTION(BlueprintCallable)
	void ChangeControlForPlayer();
	UPROPERTY(BlueprintReadWrite)
	APlayerCharater* PlayerCharacter;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> Widget;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> MapWidget;
	UPROPERTY(BlueprintReadWrite)
	UUserWidget* CarUI;
	UPROPERTY(BlueprintReadWrite)
	UUserWidget* MapUI;
	void ShowCarMap();
	void HideCarMap();
	ABaseCar();
	void DisBrake();
	UFUNCTION(BlueprintCallable)
	float GetCurrentRPM();
	float GetMaxRPM();
	UFUNCTION(BlueprintCallable)
	void ChangeAirRow();
	UFUNCTION(BlueprintCallable)
	void ReCoverAirRow();
};
