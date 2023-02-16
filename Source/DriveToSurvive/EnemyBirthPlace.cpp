// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBirthPlace.h"

#include "FPSGameModeBase.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Kismet/KismetMathLibrary.h"

void AEnemyBirthPlace::CreateEnemy()
{
	AFPSGameModeBase* Mode=Cast<AFPSGameModeBase>(GetWorld()->GetAuthGameMode());
	if(Mode)
	{
		if(Mode->CanCreateEnemy())
		{
			int RandPivote=0;
			int RandResult=rand()%EnemyTemplate.Num();
			RandPivote=RandResult<=EnemyTemplate.Num()-1?RandResult:0;
			FVector Extent=BoxComponent->GetScaledBoxExtent();
			FVector Origin=BoxComponent->GetComponentLocation();
			FVector Point=UKismetMathLibrary::RandomPointInBoundingBox(Origin, Extent);;
			ABaseEnemy* Enemy=GetWorld()->SpawnActor<ABaseEnemy>(EnemyTemplate[RandPivote],Point,FRotator(0.0f,0.0f,0.0f));
			Mode->AddEnemy(Enemy);
		}
		else
		{
			
		}
	}
}

// Sets default values
AEnemyBirthPlace::AEnemyBirthPlace()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent=CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	BoxComponent->AttachToComponent(RootComponent,FAttachmentTransformRules::KeepRelativeTransform);
	CreateTime=1.0f;
}

// Called when the game starts or when spawned
void AEnemyBirthPlace::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(Timer,this,&AEnemyBirthPlace::CreateEnemy,CreateTime,true,0);
}

// Called every frame
void AEnemyBirthPlace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

