// Fill out your copyright notice in the Description page of Project Settings.


#include "FireWorkSpawnSpace.h"

// Sets default values
AFireWorkSpawnSpace::AFireWorkSpawnSpace()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFireWorkSpawnSpace::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFireWorkSpawnSpace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFireWorkSpawnSpace::CreateFireWork()
{
	UWorld* World=GetWorld();
	if(World)
	{
		World->SpawnActor<AFireWorks>(Fire,GetActorLocation(),GetActorRotation());
	}
}

void AFireWorkSpawnSpace::StartFireWork()
{
	GetWorldTimerManager().SetTimer(Timer,this,&AFireWorkSpawnSpace::CreateFireWork,1,true);
}


