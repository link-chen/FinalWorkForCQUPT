// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FireWorks.h"
#include "GameFramework/Actor.h"
#include "FireWorkSpawnSpace.generated.h"

UCLASS()
class DRIVETOSURVIVE_API AFireWorkSpawnSpace : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSubclassOf<AFireWorks> Fire;
	FTimerHandle Timer;
	void CreateFireWork();
public:	
	// Sets default values for this actor's properties
	AFireWorkSpawnSpace();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void StartFireWork();
};
