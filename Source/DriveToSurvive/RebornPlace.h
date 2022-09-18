// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "RebornPlace.generated.h"

UCLASS()
class DRIVETOSURVIVE_API ARebornPlace : public AActor
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	UBoxComponent* Box;
	UFUNCTION()
	virtual void BeginOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:	
	// Sets default values for this actor's properties
	ARebornPlace();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
