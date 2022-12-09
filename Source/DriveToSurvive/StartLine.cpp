// Fill out your copyright notice in the Description page of Project Settings.


#include "StartLine.h"

#include "BaseCar.h"
#include "DriveToSurviveGameModeBase.h"
#include "GameFramework/GameModeBase.h"

// Sets default values
AStartLine::AStartLine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Line=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Line"));
	CrossingBox=CreateDefaultSubobject<UBoxComponent>(TEXT("CheckBox"));
	CrossingBox->SetupAttachment(RootComponent);
	Line->SetupAttachment(CrossingBox);
	FScriptDelegate ScriptDelegate;
	ScriptDelegate.BindUFunction(this,"BeginOverlap");
	CrossingBox->OnComponentBeginOverlap.Add(ScriptDelegate);
	Circle=0;
}

// Called when the game starts or when spawned
void AStartLine::BeginPlay()
{
	Super::BeginPlay();
	
}
void AStartLine::CheckFinish()
{
	bool flag=true;
	for(int i=0;i<RebornArray.Num();i++)
	{
		if(!RebornArray[i]->bCross)
			flag=false;
		RebornArray[i]->bCross=false;
	}
	if(flag)
	{
		UWorld* World=GetWorld();
		ADriveToSurviveGameModeBase* GameModeBase=Cast<ADriveToSurviveGameModeBase>(World->GetAuthGameMode());
		if(GameModeBase!=nullptr)
			GameModeBase->FinishedCircle++;
		Circle++;
	}
	if(Circle+1==TargetCircle)
	{
		UE_LOG(LogTemp,Warning,TEXT("This is finally lap of race"));
	}
	if(TargetCircle==Circle)
	{
		UE_LOG(LogTemp,Warning,TEXT("Finished"));
		for(int i=0;i<RebornArray.Num();i++)
			RebornArray[i]->StartFire();
		for(int i=0;i<FireWorkSpawnSpacesArray.Num();i++)
			FireWorkSpawnSpacesArray[i]->StartFireWork();
		FinishGame();
	}
}

// Called every frame
void AStartLine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStartLine::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(ABaseCar* Car=Cast<ABaseCar>(OtherActor))
	{
		UE_LOG(LogTemp,Warning,TEXT("CrossLine"));
		CheckFinish();
	}
}

