// Fill out your copyright notice in the Description page of Project Settings.


#include "BreakingPoint.h"

#include "FPSGameModeBase.h"

// Sets default values
ABreakingPoint::ABreakingPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Time=5;
}

// Called when the game starts or when spawned
void ABreakingPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABreakingPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABreakingPoint::SetC4()
{
	GetWorldTimerManager().SetTimer(Timer,this,&ABreakingPoint::Boom,Time,false,Time);
}

void ABreakingPoint::Boom()
{
	UE_LOG(LogTemp,Warning,TEXT("Booming"));
	for(int i=0;i<Array.Num();i++)
	{
		Array[i]->Destroy();
	}
	Cast<AFPSGameModeBase>(GetWorld()->GetAuthGameMode())->SetBreakingPoints(this);
	Destroy();
}

