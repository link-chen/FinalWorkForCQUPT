// Fill out your copyright notice in the Description page of Project Settings.


#include "CarWheel.h"

#include "BehaviorTree/BehaviorTreeTypes.h"

UCarWheel::UCarWheel()
{
	MaxLife=1000.0f;
	CurrentLife=MaxLife;
}

float UCarWheel::GetLifeRate()
{
	return CurrentLife/MaxLife;
}

void UCarWheel::Tick(float DeltaSeconds)
{
	if(CurrentLife<0.0f)
	{
		
	}
}
void UCarWheel::Wear(float Value)
{
	CurrentLife-=Value;
	UE_LOG(LogTemp,Warning,TEXT("CurrentLife==%f"),CurrentLife);
}

float UCarWheel::GetCurrentLife()
{
	return CurrentLife;
}

void UCarWheel::ReCoverTyre()
{
	CurrentLife=MaxLife;
}



