// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWeapon.h"

#include "KismetAnimationLibrary.h"
#include "Engine/StaticMeshSocket.h"
#include "Kismet/KismetSystemLibrary.h"

void ABaseWeapon::TranceSolution()
{
	UE_LOG(LogTemp,Warning,TEXT("LineTracySolution"));
}

// Sets default values
ABaseWeapon::ABaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	bFirst=true;
	bTrance=false;
	
	for(FName SocketName:MeshComponent->GetAllSocketNames())
	{
		SocketNames.Add(SocketName);
		SocketLocation.Add(FVector(0.0f));
	}
}

// Called every frame
void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bTrance)
	{
		LineTrancy();
	}
}

void ABaseWeapon::LineTrancy()
{
	if(bFirst)
	{
		for(int i=0;i<SocketNames.Num();i++)
			SocketLocation[i]=MeshComponent->GetSocketLocation(SocketNames[i]);
		bFirst=false;
		return;
	}
	for(int i=0;i<SocketNames.Num();i++)
	{
		TArray<AActor*> IgnoreActors;
		TArray<FHitResult> HitResults;
		UKismetSystemLibrary::LineTraceMulti(GetWorld(),SocketLocation[i],MeshComponent->GetSocketLocation(SocketNames[i]),TraceTypeQuery1,true,IgnoreActors,EDrawDebugTrace::None,HitResults,true);
		SocketLocation[i]=MeshComponent->GetSocketLocation(SocketNames[i]);
		for(int j=0;j<HitResults.Num();i++)
		{
			Hit.Add(HitResults[i].GetActor());
		}
	}
	UE_LOG(LogTemp,Warning,TEXT("LineTracy"));
}

void ABaseWeapon::Start()
{
	bFirst=true;
	bTrance=true;
}

void ABaseWeapon::End()
{
	bTrance=false;
	TranceSolution();
}

