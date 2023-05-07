// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehicle.h"
#include "BaseCarNPC.generated.h"

/**
 * 
 */
UCLASS()
class DRIVETOSURVIVE_API ABaseCarNPC : public AWheeledVehicle
{
	GENERATED_BODY()

public:
	ABaseCarNPC();
	virtual void Tick(float DeltaSeconds) override;
};
