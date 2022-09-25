// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CarUpdateMessage.h"
#include "GameFramework/GameModeBase.h"
#include "DriveToSurviveGameModeBase.generated.h"

class ABaseCar;
/**
 * 
 */
UCLASS()
class DRIVETOSURVIVE_API ADriveToSurviveGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	FTimerHandle Time;
	int LeftTime;
	virtual void BeginPlay() override;
	void CountTime();
	bool bCanCarRun;
	int Money;
	CarUpdateMessage* CarMessage;
	ABaseCar* PlayerCar;
public:
	UPROPERTY(BlueprintReadWrite)
	int FinishedCircle;
	bool GetCarRunable();
	UFUNCTION(BlueprintCallable)
	void SaveGameMessage();
	UFUNCTION(BlueprintCallable)
	void ReadGameMessage();
	ADriveToSurviveGameModeBase();
};
