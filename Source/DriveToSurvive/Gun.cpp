// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/AudioComponent.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GunMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Audio=CreateDefaultSubobject<UAudioComponent>(TEXT("AudiComponent"));
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();

	GunBullte=MaxBullte;
}

void AGun::Fire()
{
	UWorld* World=GetWorld();
	if(World)
	{
		if(GunBullte)
		{
			World->SpawnActor<AGunBullte>(Bullte,GetActorLocation(),GetActorRotation());
			Audio->Play();
		}
	}
}

float AGun::GetShotTime()
{
	return ShotTime;
}

void AGun::ReLoadBullte()
{
	if(LeftGunBullte>=MaxBullte)
	{
		if(GunBullte!=0)
			LeftGunBullte-=(MaxBullte-GunBullte);	
		else
			LeftGunBullte-=MaxBullte;
		GunBullte=MaxBullte;
	}
	else
	{
		if(LeftGunBullte+GunBullte<=MaxBullte)
		{
			GunBullte+=LeftGunBullte;
			LeftGunBullte=0;
		}
		else
		{
			LeftGunBullte=(GunBullte+LeftGunBullte)-MaxBullte;
			GunBullte=MaxBullte;
		}
	}
}



// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

