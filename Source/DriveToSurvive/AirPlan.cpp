// Fill out your copyright notice in the Description page of Project Settings.


#include "AirPlan.h"

#include "BaseCar.h"

// Sets default values
AAirPlan::AAirPlan()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent=CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
	Box=CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->AttachToComponent(MeshComponent,FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AAirPlan::BeginPlay()
{
	Super::BeginPlay();

	FScriptDelegate Delegate;
	Delegate.BindUFunction(this,"OnOverlayBegin");
	Box->OnComponentBeginOverlap.Add(Delegate);
}
void AAirPlan::OnOverlayBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp,Warning,TEXT("BoxHere"));
	if(ABaseCar* Car=Cast<ABaseCar>(OtherActor))
	{
		UE_LOG(LogTemp,Warning,TEXT("CarEnter"));
	}
	if(APlayerCharater* Player=Cast<APlayerCharater>(OtherActor))
	{
		UE_LOG(LogTemp,Warning,TEXT("PlayerEnter"));
	}
}

void AAirPlan::EndOverLap(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp)
{
	if(ABaseCar* Car=Cast<ABaseCar>(Other))
	{
		
	}
	if(APlayerCharater* Player=Cast<APlayerCharater>(Other))
	{
		
	}
}

// Called every frame
void AAirPlan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

