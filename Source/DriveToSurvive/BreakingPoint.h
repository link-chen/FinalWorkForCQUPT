// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BreakingPoint.generated.h"

UCLASS()
class DRIVETOSURVIVE_API ABreakingPoint : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComponent;
	UPROPERTY(EditAnywhere)
	int Time;
	FTimerHandle Timer;
public:	
	// Sets default values for this actor's properties
	ABreakingPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetC4();
	void Boom();
};
