// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxStation.h"

// Sets default values
ABoxStation::ABoxStation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box=CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	FScriptDelegate BoxDel;
	BoxDel.BindUFunction(this,"OnOverlayBegin");
	Box->OnComponentBeginOverlap.Add(BoxDel);
}

// Called when the game starts or when spawned
void ABoxStation::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoxStation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABoxStation::OnOverlayBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}


