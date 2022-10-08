// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PointLightComponent.h"
#include "GameFramework/Actor.h"
#include "LampLight.generated.h"

UCLASS()
class DRIVETOSURVIVE_API ALampLight : public AActor
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent *Lamp;
	UPROPERTY(EditAnywhere)
	UPointLightComponent* LightComponent;
public:	
	// Sets default values for this actor's properties
	ALampLight();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
