// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class DRIVETOSURVIVE_API CarUpdateMessage
{
public:
	float ERSRate;
	int Mass;
	float ChangeGeerTime;
	float ReChargeRate;
	CarUpdateMessage();
	~CarUpdateMessage();
};
