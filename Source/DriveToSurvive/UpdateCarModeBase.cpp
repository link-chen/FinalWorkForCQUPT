// Fill out your copyright notice in the Description page of Project Settings.


#include "UpdateCarModeBase.h"

#include "BaseCar.h"
#include "DTSSaveGame.h"
#include "Kismet/GameplayStatics.h"

AUpdateCarModeBase::AUpdateCarModeBase()
{
	
}

void AUpdateCarModeBase::BeginPlay()
{
	Super::BeginPlay();
	BaseCar=Cast<ABaseCar>(GetWorld()->GetFirstPlayerController()->GetPawn());
	ReadGameMessage();
}

void AUpdateCarModeBase::SaveGameMessage()
{
	if(UDTSSaveGame* Save=Cast<UDTSSaveGame>(UGameplayStatics::CreateSaveGameObject(UDTSSaveGame::StaticClass())))
	{
		Save->ERSRate=ERSRate;
		Save->MaxElectronicPower=MaxElectronicPower;
		Save->Point=Point;
		Save->DownForceRate=DownForceRate;
		Save->Mass=Mass;
		Save->ReChargeRate=ReChargeRate;
		Save->ChangeGearTime=ChangeGearTime;
		if(UGameplayStatics::SaveGameToSlot(Save,"SaveSlot",0))
		{
			
		}
	}
}

void AUpdateCarModeBase::ReadGameMessage()
{
	if(UDTSSaveGame* Read=Cast<UDTSSaveGame>(UGameplayStatics::LoadGameFromSlot("SaveSlot",0)))
	{
		ERSRate=Read->ERSRate;
		MaxElectronicPower=Read->MaxElectronicPower;
		Point=Read->Point;
		DownForceRate=Read->DownForceRate;
		Mass=Read->Mass;
		ReChargeRate=Read->ReChargeRate;
		ChangeGearTime=Read->ChangeGearTime;
	}else
	{
		ERSRate=BaseCar->GetERSRate();
		MaxElectronicPower=BaseCar->MaxElectronicPower;
		DownForceRate=0.0f;
		Mass=2750.0f;
		ChangeGearTime=4.5f;
		Point=5760;
		ReChargeRate=0.00005f;
	}
}

void AUpdateCarModeBase::UpdateERS(int Change)
{
	if(Change==1)
	{
		if(ERSRate+0.5<=6.0&&Point>=1)
		{
			ERSRate+=0.5;
			Point--;
			SaveGameMessage();
		}
		else
			MaxLevel();
		UE_LOG(LogTemp,Warning,TEXT("UpdateERS"));
	}
	if(Change==-1)
	{
		if(ERSRate-0.5>=0)
		{
			ERSRate-=0.5;
			Point++;
			SaveGameMessage();
		}
		else
			MinLevle();
	}
}

void AUpdateCarModeBase::UpdateElectronic(int Change)
{
	if(Change==1)
	{
		if(Point>=1)
		{
			MaxElectronicPower+=100.0f;
			Point--;
			SaveGameMessage();
		}
		else
			MaxLevel();
	}
	if(Change==-1)
	{
		if(MaxElectronicPower-100.0f>=1000.0f)
		{
			MaxElectronicPower-=10.0f;
			Point++;
			SaveGameMessage();
		}
		else
			MinLevle();
	}
}

void AUpdateCarModeBase::UpdateMass(int Change)
{
	if(Change==1)
	{
		if(Mass-10>=750)
		{
			Mass-=10;
			Point--;
			SaveGameMessage();
		}
		else
			MaxLevel();
	}
	if(Change==-1)
	{
		if(Mass+10<=2750)
		{
			Mass+=10;
			Point++;
			SaveGameMessage();
		}
		else
			MinLevle();
	}
}

void AUpdateCarModeBase::UpdateDownForce(int Change)
{
	if(Change==1)
	{
		if(Point>=1){
			DownForceRate+=0.1;
			Point--;
			SaveGameMessage();
		}else
			MaxLevel();
	}
	if(Change==-1)
	{
		if(DownForceRate-0.1f>=0.0f)
		{
			DownForceRate-=0.1f;
			Point++;
			SaveGameMessage();
		}
		else
			MinLevle();
	}
}

void AUpdateCarModeBase::UpdateReCharge(int Change)
{
	if(Change==1)
	{
		if(Point>=1&&ReChargeRate<=0.99f)
		{
			ReChargeRate+=0.000075f;
			Point--;
			SaveGameMessage();
		}
		else
			MaxLevel();
	}
	if(Change==-1)
	{
		if(ReChargeRate>=0.00006f)
		{
			Point++;
			ReChargeRate-=0.000075f;
			SaveGameMessage();
		}
		else
			MinLevle();
	}
}

void AUpdateCarModeBase::UpdateChangeGear(int Change)
{
	if(Change==1)
	{
		if(ChangeGearTime>=0.1f&&Point>=1)
		{
			Point--;
			ChangeGearTime-=0.05f;
			SaveGameMessage();
		}
		else
			MaxLevel();
	}
	if(Change==-1)
	{
		if(ChangeGearTime<=4.5f)
		{
			Point++;
			ChangeGearTime+=0.05f;
			SaveGameMessage();
		}
		else
		{
			MinLevle();
		}
	}
}

