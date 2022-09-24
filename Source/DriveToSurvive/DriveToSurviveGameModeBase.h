// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DriveToSurviveGameModeBase.generated.h"

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
