// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "TPSSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class DRIVETOSURVIVE_API UTPSSaveGame : public USaveGame
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<int> FinishedTask;

	UPROPERTY()
	TArray<int> TargetActorNum;

public:
	UPROPERTY()
	TArray<int> PlayerTargetActorNum;
	UPROPERTY()
	TArray<int> CollectedTargetActorNum;
	UPROPERTY()
	FVector ReStartLocation;
	UPROPERTY()
	FString SaveSlotName;
	UPROPERTY()
	uint32 UserIndex;
	UPROPERTY()
	bool bFinishTPS;
	
	UTPSSaveGame();
};
