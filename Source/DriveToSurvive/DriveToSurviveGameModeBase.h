// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DriveToSurviveGameModeBase.generated.h"

/**
 * 
 */
enum class EGameState :short {
	EWait,
	EPlaying,
};
UCLASS()
class DRIVETOSURVIVE_API ADriveToSurviveGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	FTimerHandle Time;
	int LeftTime;
	EGameState CurrentState;
	virtual void BeginPlay() override;
	void CountTime();
public:
	EGameState GetGameState();
	ADriveToSurviveGameModeBase();
};
