// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PointLightComponent.h"
#include "GameFramework/Actor.h"
#include "SignalLight.generated.h"

UCLASS()
class DRIVETOSURVIVE_API ASignalLight : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<UPointLightComponent*> LightArray;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh;
public:	
	// Sets default values for this actor's properties
	ASignalLight();

	UFUNCTION(BlueprintCallable)
	void CloseLight(int Pivote);
	UFUNCTION(BlueprintCallable)
	void CloseLightSecondPart();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
