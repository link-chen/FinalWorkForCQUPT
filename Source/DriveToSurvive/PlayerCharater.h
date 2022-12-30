// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gun.h"
#include "GameFramework/Character.h"
#include "PlayerCharater.generated.h"

UCLASS()
class DRIVETOSURVIVE_API APlayerCharater : public ACharacter
{
	GENERATED_BODY()
	
	void MoveForward(float Value);
	void MoveRight(float Value);

	FTimerHandle Timer;
	
	void UseGun();
	void StopGun();
	void GunFire();

	AGun* PlayerGun;

	TArray<AGun*> GunList;

	void DisCardGun();
	void ReLoad();

	bool bRun;

	void ActiveMode();
	
	UFUNCTION()
	virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp,
	bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
public:
	// Sets default values for this character's properties
	APlayerCharater();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
