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
		Light->SetupAttachment(StaticMesh);
		Light->SetLightColor(FLinearColor(255.0f,0.0f,0.0f));
		LightArray.Add(Light);
	}
}

// Called when the game starts or when spawned
void ASignalLight::BeginPlay()
{
	Super::BeginPlay();
	for(int i=0;i<LightArray.Num();i++)
		LightArray[i]->SetIntensity(0.0f);
}

// Called every frame
void ASignalLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASignalLight::CloseLight(int Pivote)
{
	if(Pivote>=5&&Pivote<0)
		return;
	UE_LOG(LogTemp,Warning,TEXT("LightArray[%d] on"),Pivote);
	LightArray[Pivote]->SetIntensity(10000.0f);
}

void ASignalLight::CloseLightSecondPart()
{
	for(int i=0;i<LightArray.Num();i++)
		LightArray[i]->SetIntensity(0.0f);
}




