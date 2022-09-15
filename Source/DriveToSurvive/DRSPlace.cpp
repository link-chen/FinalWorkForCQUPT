// Fill out your copyright notice in the Description page of Project Settings.


#include "DRSPlace.h"

#include "BaseCar.h"

// Sets default values
ADRSPlace::ADRSPlace()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DRSStart=CreateDefaultSubobject<UBoxComponent>(TEXT("DRSStart"));
	DRSEnd=CreateDefaultSubobject<UBoxComponent>(TEXT("DRSEnd"));

	FScriptDelegate Start;
	Start.BindUFunction(this,"DRSStartFunction");
	DRSStart->OnComponentBeginOverlap.Add(Start);
	FScriptDelegate End;
	End.BindUFunction(this,"DRSEndFunction");
	DRSEnd->OnComponentBeginOverlap.Add(End);
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
	if(ABaseCar* Car=Cast<ABaseCar>(OtherActor))
	{
		if(Car->bCanUseDRS)
		{
			Car->MaxSpeed+=25.0f;
			UE_LOG(LogTemp,Warning,TEXT("DRSStart"));
		}
	}
}

void ADRSPlace::DRSEndFunction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(ABaseCar* Car=Cast<ABaseCar>(OtherActor))
	{
		if(Car->bCanUseDRS)
		{
			Car->bCanUseDRS=false;
			Car->MaxSpeed-=25.0f;
			UE_LOG(LogTemp,Warning,TEXT("DRSEnd"));
		}
	}
}

