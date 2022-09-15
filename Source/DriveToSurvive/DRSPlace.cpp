// Fill out your copyright notice in the Description page of Project Settings.


#include "DRSPlace.h"

// Sets default values
ADRSPlace::ADRSPlace()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DRSStart=CreateDefaultSubobject<UBoxComponent>(TEXT("DRSStart"));
	DRSEnd=CreateDefaultSubobject<UBoxComponent>(TEXT("DRSEnd"));

	FScriptDelegate Start;
	FScriptDelegate End;
}

// Called when the game starts or when spawned
void ADRSPlace::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADRSPlace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADRSPlace::DRSStartFunction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

void ADRSPlace::DRSEndFunction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

