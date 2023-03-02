// Fill out your copyright notice in the Description page of Project Settings.


#include "AirPlan.h"

#include "BaseCar.h"
#include "DTSSaveGame.h"
#include "TPSSaveGame.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAirPlan::AAirPlan()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent=CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
	Box=CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->AttachToComponent(MeshComponent,FAttachmentTransformRules::KeepRelativeTransform);
	CheckPlayerComponent=CreateDefaultSubobject<UBoxComponent>(TEXT("CheckPlayerComponent"));
	CheckPlayerComponent->AttachToComponent(MeshComponent,FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AAirPlan::BeginPlay()
{
	Super::BeginPlay();
	FScriptDelegate Del;
	Del.BindUFunction(this,"OnOverlayBegin");
	Box->OnComponentBeginOverlap.Add(Del);
}
void AAirPlan::OnOverlayBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(ABaseCar* PlayerCar=Cast<ABaseCar>(OtherActor))
	{
		//Car->AttachToComponent(MeshComponent,FAttachmentTransformRules::KeepWorldTransform,"skeleton_grp插槽");
		UE_LOG(LogTemp,Warning,TEXT("Finish"));
		if(UTPSSaveGame* Save=Cast<UTPSSaveGame>(UGameplayStatics::CreateSaveGameObject(UTPSSaveGame::StaticClass())))
		{
			Save->bFinishTPS=true;
			if(UGameplayStatics::SaveGameToSlot(Save,"TPSSaveSlot",1))
			{
				
			}
		}
	}
}

void AAirPlan::EndOverLap(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp)
{
	if(Cast<ABaseCar>(Other))
	{
		
	}
}

// Called every frame
void AAirPlan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

