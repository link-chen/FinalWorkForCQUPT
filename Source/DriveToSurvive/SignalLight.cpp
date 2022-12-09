// Fill out your copyright notice in the Description page of Project Settings.


#include "SignalLight.h"

// Sets default values
ASignalLight::ASignalLight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	for(int i=0;i<5;i++)
	{
		UPointLightComponent* Light=CreateDefaultSubobject<UPointLightComponent>(TEXT("Light"+i));
		LightArray.Add(Light);
	}
}

// Called when the game starts or when spawned
void ASignalLight::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASignalLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



