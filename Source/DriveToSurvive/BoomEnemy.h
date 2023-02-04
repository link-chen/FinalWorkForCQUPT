// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemy.h"
#include "BoomEnemy.generated.h"

/**
 * 
 */
UCLASS()
class DRIVETOSURVIVE_API ABoomEnemy : public ABaseEnemy
{
	GENERATED_BODY()
public:
	virtual void Death() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	virtual void GetHurt(float Value) override;
	virtual void PlayDeathAnimation() override;
};
