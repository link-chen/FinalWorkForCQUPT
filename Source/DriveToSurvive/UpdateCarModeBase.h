// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UpdateCarModeBase.generated.h"

/**
 * 
 */
class ABaseCar;
UCLASS()
class DRIVETOSURVIVE_API AUpdateCarModeBase : public AGameModeBase
{
	GENERATED_BODY()

	ABaseCar* BaseCar;

	void SaveGameMessage();
	void ReadGameMessage();
	
public:
	UPROPERTY(BlueprintReadOnly)
	int Point;
	UPROPERTY()
	float ERSRate;
	UPROPERTY()
	int Mass;
	UPROPERTY()
	float MaxElectronicPower;
	UPROPERTY()
	float DownForceRate;
	UPROPERTY()
	float ReChargeRate;
	UPROPERTY()
	float ChangeGeerTime;
	AUpdateCarModeBase();
	UFUNCTION(BlueprintCallable)
	void UpdateERS(int Change);
	UFUNCTION(BlueprintCallable)
	void UpdateElectronic(int Change);	
	UFUNCTION(BlueprintCallable)
	void UpdateMass(int Change);
	UFUNCTION(BlueprintCallable)
	void UpdateDownForce(int Change);
	UFUNCTION(BlueprintCallable)
	void UpdateReCharge(int Change);
	UFUNCTION(BlueprintCallable)
	void UpdateChangeGear(int Change);
	virtual void BeginPlay() override;
};
