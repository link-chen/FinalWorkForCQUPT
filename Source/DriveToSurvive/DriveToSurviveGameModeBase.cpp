// Copyright Epic Games, Inc. All Rights Reserved.


#include "DriveToSurviveGameModeBase.h"

#include "BaseCar.h"
#include "DTSSaveGame.h"
#include "SignalLight.h"
#include "StartLine.h"
#include "WheeledVehicleMovementComponent.h"
#include "WheeledVehicleMovementComponent4W.h"
#include "GameFramework/GameSession.h"
#include "Kismet/GameplayStatics.h"

class ABaseCar;

ADriveToSurviveGameModeBase::ADriveToSurviveGameModeBase()
{
	LeftTime=5;
	Point=576;
}
void ADriveToSurviveGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	bCanCarRun=false;
	PlayerCar=Cast<ABaseCar>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if(PlayerCar!=nullptr)
	ReadGameMessage();
 
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), Actors);
 
	for (AActor* Actor : Actors)
	{
		if(AStartLine* Line=Cast<AStartLine>(Actor))
		{
			StartLine=Line;
		}
		if(ASignalLight* Signal=Cast<ASignalLight>(Actor))
		{
			SignalLight=Signal;
		}
	}
}
void ADriveToSurviveGameModeBase::CountTime()
{
	if(LeftTime!=0)
	{
		LeftTime--;
		Signal();
		if(SignalLight)
		{
			SignalLight->CloseLight(LeftTime);
		}
	}
	else
	{
		bCanCarRun=true;
		StartLine->SetCrossTime();
		if(SignalLight)
			SignalLight->CloseLightSecondPart();
		GetWorldTimerManager().ClearTimer(Time);
		PlayerCar->ShowRunning();
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
		Save->MaxElectronicPower=PlayerCar->ElectronicPower;
		Save->ERSRate=PlayerCar->GetERSRate();
		Save->Mass=PlayerCar->GetVehicleMovementComponent()->Mass;
		Save->Point=Point;
		Save->DownForceRate=PlayerCar->GetDownForceRate();
		Save->ReChargeRate=PlayerCar->GetReChargeRate();
		UWheeledVehicleMovementComponent4W* WheelMoveComponent=Cast<UWheeledVehicleMovementComponent4W>(PlayerCar->GetVehicleMovementComponent());
		Save->ChangeGearTime=WheelMoveComponent->TransmissionSetup.GearSwitchTime;

		//异步任务委托
		FAsyncSaveGameToSlotDelegate SaveDelegate;
		//启动异步保存进程
		UGameplayStatics::AsyncSaveGameToSlot(Save, TEXT("SaveSlot"), 0, SaveDelegate);
	}
}

void ADriveToSurviveGameModeBase::Save()
{
	
}

void ADriveToSurviveGameModeBase::ReadGameMessage()
{
	if(UDTSSaveGame* Read=Cast<UDTSSaveGame>(UGameplayStatics::LoadGameFromSlot("SaveSlot",0)))
	{
		FinishedCircle=Read->FinishedCircle;
		Point=Read->Point;
		PlayerCar->MaxElectronicPower=Read->MaxElectronicPower;
		PlayerCar->SetERSRate(Read->ERSRate);
		PlayerCar->GetVehicleMovementComponent()->Mass=Read->Mass;
		PlayerCar->SetDownForceRate(Read->DownForceRate);
		PlayerCar->SetReChargeRate(Read->ReChargeRate);
		PlayerCar->SetSwitchGearTime(Read->ChangeGearTime);
		UE_LOG(LogTemp,Warning,TEXT("CarDownForceRate==%f"),Read->DownForceRate);
	}
}

void ADriveToSurviveGameModeBase::StartCountLight()
{
	GetWorldTimerManager().SetTimer(Time,this,&ADriveToSurviveGameModeBase::CountTime,1,true);
}
