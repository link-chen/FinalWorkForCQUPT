// Fill out your copyright notice in the Description page of Project Settings.


#include "LampLight.h"

// Sets default values
ALampLight::ALampLight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Lamp=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Lamp"));
	LightComponent=CreateDefaultSubobject<UPointLightComponent>(TEXT("Light"));
	LightComponent->SetupAttachment(Lamp);
	LightComponent->SetRelativeLocation(Lamp->GetRelativeLocation());
}

// Called when the game starts or when spawned
void ALampLight::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALampLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

