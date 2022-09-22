// Copyright Epic Games, Inc. All Rights Reserved.


#include "DriveToSurviveGameModeBase.h"

ADriveToSurviveGameModeBase::ADriveToSurviveGameModeBase()
{
	LeftTime=5;
}
void ADriveToSurviveGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp,Warning,TEXT("LightCount"));
	bCanCarRun=false;
	GetWorldTimerManager().SetTimer(Time,this,&ADriveToSurviveGameModeBase::CountTime,1,true);
}
void ADriveToSurviveGameModeBase::CountTime()
{
	if(LeftTime!=0)
		LeftTime--;
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("It's Light out and here we go"));
		bCanCarRun=true;
		GetWorldTimerManager().ClearTimer(Time);
	}
}
bool ADriveToSurviveGameModeBase::GetCarRunable()
{
	return bCanCarRun;
}
