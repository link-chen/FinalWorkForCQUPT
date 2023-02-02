// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPSGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class DRIVETOSURVIVE_API AFPSGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	bool bFinishTask;
	bool bBossKilled;
	void SaveGameMessage();
	void ReadGameMessage();

public:
	UPROPERTY(EditAnywhere)
	int TotalTargetNum;
	UPROPERTY(EditAnywhere)
	TArray<int> TargetArray;
	AFPSGameModeBase();
};
