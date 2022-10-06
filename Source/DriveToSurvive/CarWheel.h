// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VehicleWheel.h"
#include "CarWheel.generated.h"

/**
 * 
 */
UCLASS()
class DRIVETOSURVIVE_API UCarWheel : public UVehicleWheel
{
	GENERATED_BODY()
private:
	float MaxLife;
	float CurrentLife;
public:
	UCarWheel();
	virtual void Tick(float DeltaSeconds) override;
	void Wear(float Value);//磨损
	float GetLifeRate();
	float GetCurrentLife();
};
