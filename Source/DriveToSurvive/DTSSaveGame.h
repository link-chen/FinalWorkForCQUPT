// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "DTSSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class DRIVETOSURVIVE_API UDTSSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FString SaveSlotName;
	UPROPERTY()
	uint32 UserIndex;
	UPROPERTY()
	int FinishedCircle;
	//
	UPROPERTY()
	int Money;
	UPROPERTY()
	int ERSLevel;
	UPROPERTY()
	float ERSRate;
	UPROPERTY()
	int MassLevel;
	UPROPERTY()
	int Mass;
	UPROPERTY()
	int ElectronicLevel;
	UPROPERTY()
	float MaxElectronicPower;
	UPROPERTY()
	int GeerLevel;
	UPROPERTY()
	float ChangeGeerTime;
	UDTSSaveGame();
};
