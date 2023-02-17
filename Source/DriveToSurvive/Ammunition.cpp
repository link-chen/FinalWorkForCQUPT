// Fill out your copyright notice in the Description page of Project Settings.


#include "Ammunition.h"

// Sets default values
AAmmunition::AAmmunition()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AAmmunition::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAmmunition::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAmmunition::AddAmmunition(AGun* Gun0, AGun* Gun1)
{
	if(Gun0)
	{
		Gun0->ReLoadAllBullte();
	}
	if(Gun1)
	{
		Gun1->ReLoadAllBullte();
	}
}

