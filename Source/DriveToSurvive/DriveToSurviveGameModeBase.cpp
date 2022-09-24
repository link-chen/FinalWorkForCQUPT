// Copyright Epic Games, Inc. All Rights Reserved.


#include "DriveToSurviveGameModeBase.h"

#include "DTSSaveGame.h"
#include "Kismet/GameplayStatics.h"

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
	ReadGameMessage();
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

void ADriveToSurviveGameModeBase::SaveGameMessage()
{
	if(UDTSSaveGame* Save=Cast<UDTSSaveGame>(UGameplayStatics::CreateSaveGameObject(UDTSSaveGame::StaticClass())))
	{
		Save->FinishedCircle=FinishedCircle;
		UE_LOG(LogTemp,Warning,TEXT("SaveGame"));
		if(UGameplayStatics::SaveGameToSlot(Save,"SaveSlot",0))
		{
			
		}
	}
}

void ADriveToSurviveGameModeBase::ReadGameMessage()
{
	if(UDTSSaveGame* Read=Cast<UDTSSaveGame>(UGameplayStatics::LoadGameFromSlot("SaveSlot",0)))
	{
		UE_LOG(LogTemp,Warning,TEXT("ReadingMessage"));
		FinishedCircle=Read->FinishedCircle;
		UE_LOG(LogTemp,Warning,TEXT("FinishedCircle==%d"),Read->FinishedCircle);
	}
}
