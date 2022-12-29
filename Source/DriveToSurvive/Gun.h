// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GunBullte.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class DRIVETOSURVIVE_API AGun : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* GunMesh;
	
	UPROPERTY(EditAnywhere)
	float ShotTime;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AGunBullte> Bullte;

	UPROPERTY(EditAnywhere)
	FString GunName;

	UPROPERTY(EditAnywhere)
	UAudioComponent* Audio;

	UPROPERTY(EditAnywhere)
	int GunBullte;

	UPROPERTY(EditAnywhere)
	int LeftGunBullte;
	
public:	
	// Sets default values for this actor's properties
	AGun();

	void Fire();
	float GetShotTime();

	void ReLoadBullte();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
