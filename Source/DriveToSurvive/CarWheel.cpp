// Fill out your copyright notice in the Description page of Project Settings.


#include "CarWheel.h"

#include "PhysXInterfaceWrapperCore.h"
#include "Shape.h"


UCarWheel::UCarWheel()
{
	MaxLife=1000.0f;
	CurrentLife=MaxLife;
	bDraw=false;
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
	if(bDraw)
		UE_LOG(LogTemp,Warning,TEXT("HHHHHH"));
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

void UCarWheel::CreateMaterial()
{
	bDraw=true;
}

void UCarWheel::StopDraw()
{
	bDraw=false;
}

