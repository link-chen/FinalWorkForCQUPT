// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameChoose.generated.h"

/**
 * 
 */
UCLASS()
class DRIVETOSURVIVE_API AGameChoose : public AGameModeBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void CheckFinish();
	UFUNCTION(BlueprintImplementableEvent)
	void EnterTPSMode();
	bool GetFinish();
};
