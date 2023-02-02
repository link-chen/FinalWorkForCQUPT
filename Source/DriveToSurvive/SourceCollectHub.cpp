// Fill out your copyright notice in the Description page of Project Settings.


#include "SourceCollectHub.h"

#include "FPSGameModeBase.h"
#include "TPSSaveGame.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASourceCollectHub::ASourceCollectHub()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));

}

// Called when the game starts or when spawned
void ASourceCollectHub::BeginPlay()
{
	Super::BeginPlay();

	Read();
}

// Called every frame
void ASourceCollectHub::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASourceCollectHub::GetPlayerSource(TArray<int> PlayerTargetArray)
{
	for(int i=0;i<CollectedSourceArray.Num();i++)
		CollectedSourceArray[i]+=PlayerTargetArray[i];
	Save();
}

void ASourceCollectHub::Read()
{
	if(UTPSSaveGame* Read=Cast<UTPSSaveGame>(UGameplayStatics::LoadGameFromSlot("TPSSaveSlot",1)))
	{
		if(Read->CollectedTargetActorNum.Num()==0)
		{
			for(int i=0;i<Cast<AFPSGameModeBase>(GetWorld()->GetAuthGameMode())->TotalTargetNum;i++)
				CollectedSourceArray.Add(0);
		}
		else
		{
			for(int i=0;i<Read->CollectedTargetActorNum.Num();i++)
				CollectedSourceArray.Add(Read->CollectedTargetActorNum[i]);
		}
	}
	else
	{
		for(int i=0;i<Cast<AFPSGameModeBase>(GetWorld()->GetAuthGameMode())->TotalTargetNum;i++)
			CollectedSourceArray.Add(0);
	}
}

void ASourceCollectHub::Save()
{
	if(UTPSSaveGame* Save=Cast<UTPSSaveGame>(UGameplayStatics::CreateSaveGameObject(UTPSSaveGame::StaticClass())))
	{
		Save->CollectedTargetActorNum=CollectedSourceArray;
		if(UGameplayStatics::SaveGameToSlot(Save,"TPSSaveSlot",1))
		{
			
		}
	}
}

