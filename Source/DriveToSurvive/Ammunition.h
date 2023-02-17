// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gun.h"
#include "GameFramework/Actor.h"
#include "Ammunition.generated.h"

UCLASS()
class DRIVETOSURVIVE_API AAmmunition : public AActor
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComponent;
public:	
	// Sets default values for this actor's properties
	AAmmunition();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddAmmunition(AGun* Gun0,AGun* Gun1);
};
