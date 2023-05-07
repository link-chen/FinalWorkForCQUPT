// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VehicleWheel.h"
#include "Tickable.h"
#include "CarWheel.generated.h"

/**
 * 
 */
UCLASS()
class DRIVETOSURVIVE_API UCarWheel : public UVehicleWheel

{
	GENERATED_BODY()
private:
	float DestoryNum;
	UPROPERTY(EditAnywhere)
	float WheelRate;
	const float Pi=3.1415926f;
	void CaculatePerformance();
	UPROPERTY(EditAnywhere)
	float RateForLine;
	UPROPERTY(EditAnywhere)
	float MaxPerformance;
	UPROPERTY(EditAnywhere)
	float RateForPow;
	UPROPERTY(EditAnywhere)
	float MaxDestoryNum;
	float Cliff;
	float WorstPerformace;
	float CurrentPerformance;
	bool bFirst;
	float Lat;
public:
	UCarWheel();
	virtual void Tick(float DeltaSeconds) override;
	void Wear(float Value);//磨损
	float GetLifeRate();
	float GetCurrentLife();
	void ReCoverTyre();
	float GetWheelSize();
	float GetWheelLength();
	float GetWheelMass();
};
