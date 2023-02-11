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
	FScriptDelegate Del;
	Del.BindUFunction(this,"OnOverlayBegin");
	Box->OnComponentBeginOverlap.Add(Del);
}
void AAirPlan::OnOverlayBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(ABaseCar* Car=Cast<ABaseCar>(OtherActor))
	{
		UE_LOG(LogTemp,Warning,TEXT("CarEnter"));
		//Car->AttachToComponent(MeshComponent,FAttachmentTransformRules::KeepWorldTransform,"skeleton_grp插槽");
	}
}

void AAirPlan::EndOverLap(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp)
{
	
}

// Called every frame
void AAirPlan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

