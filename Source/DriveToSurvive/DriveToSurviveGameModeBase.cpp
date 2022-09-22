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
	CurrentState=EGameState::EWait;
	GetWorldTimerManager().SetTimer(Time,this,&ADriveToSurviveGameModeBase::CountTime,1,true);
}
void ADriveToSurviveGameModeBase::CountTime()
{
	if(LeftTime!=0)
		LeftTime--;
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("It's Light out and here we go"));
		CurrentState=EGameState::EPlaying;
		GetWorldTimerManager().ClearTimer(Time);
	}
}

EGameState ADriveToSurviveGameModeBase::GetGameState()
{
	return CurrentState;
}

