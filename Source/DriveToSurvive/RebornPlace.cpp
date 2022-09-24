// Fill out your copyright notice in the Description page of Project Settings.


#include "RebornPlace.h"

#include "BaseCar.h"

// Sets default values
ARebornPlace::ARebornPlace()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Box=CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));

	FScriptDelegate Del;
	Del.BindUFunction(this,"BeginOverLap");
	Box->OnComponentBeginOverlap.Add(Del);
	bCross=false;
}

// Called when the game starts or when spawned
void ARebornPlace::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARebornPlace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARebornPlace::BeginOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(ABaseCar* Car=Cast<ABaseCar>(OtherActor))
	{
		Car->LastLocation=Car->GetTransform().GetLocation();
		Car->ReBornRotator=Car->GetTransform().Rotator();
		bCross=true;
	}
}

