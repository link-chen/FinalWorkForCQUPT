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
	UStaticMeshComponent* FireMesh;
	
	UPROPERTY(EditAnywhere)
	float ShotTime;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AGunBullte> Bullte;

	UPROPERTY(EditAnywhere)
	FString GunName;

	UPROPERTY(EditAnywhere)
	UAudioComponent* Audio;
	
	int GunBullte;

	UPROPERTY(EditAnywhere)
	int MaxBullte;

	UPROPERTY(EditAnywhere)
	int LeftGunBullte;

	FVector GetFireLocation();
	FRotator GetFireRotator();

	void UseBullte();
	
public:	
	// Sets default values for this actor's properties
	AGun();

	void Fire();
	float GetShotTime();

	void ReLoadBullte();

	void GiveUp();

	bool bCanUse;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
