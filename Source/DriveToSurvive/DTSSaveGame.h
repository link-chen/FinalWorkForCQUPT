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
	float ChangeGearTime;
	UPROPERTY()
	bool bFinish;
	UDTSSaveGame();
};
