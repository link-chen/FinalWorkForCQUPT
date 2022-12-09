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
	virtual void BeginPlay() override;
	void CountTime();
	bool bCanCarRun;
	CarUpdateMessage* CarMessage;
	ABaseCar* PlayerCar;
public:
	UPROPERTY(BlueprintReadOnly)
	int LeftTime;
	UPROPERTY(BlueprintReadWrite)
	int FinishedCircle;
	UPROPERTY(BlueprintReadWrite)
	int Point;
	bool GetCarRunable();
	UFUNCTION(BlueprintCallable)
	void SaveGameMessage();
	UFUNCTION(BlueprintCallable)
	void ReadGameMessage();
	ADriveToSurviveGameModeBase();
	UFUNCTION(BlueprintCallable)
	void StartCountLight();
	UFUNCTION(BlueprintImplementableEvent)
	void Signal();
};
