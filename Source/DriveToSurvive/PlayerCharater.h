// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gun.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
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
	AGun* PlayerGun1;

	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;
	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArm;

	TArray<AGun*> GunList;

	UPROPERTY(EditAnywhere)
	float WalkSpeed;
	UPROPERTY(EditAnywhere)
	float RunSpeed;
	
	void DisCardGun();
	void ReLoad();

	bool bRun;

	// 按下键时，设置跳跃标记。
	UFUNCTION()
	void StartJump();

	// 释放键时，清除跳跃标记。
	UFUNCTION()
	void StopJump();
	
	void ActiveMode();
	void CanncelActiveMode();

	void TakeWeaponOne();
	void TakeWeaponTwo();

	void TakeWeaponRelease();

	UPROPERTY(EditAnywhere)
	FVector GunAttachLocationOne;
	UPROPERTY(EditAnywhere)
	FVector GunAttachLocationTwo;

	UPROPERTY(EditAnywhere)
	FVector FightGunAttachLocation;
	
	
	UFUNCTION()
	virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp,
	bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

	UFUNCTION()
	virtual  void OnOverlayBegin(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit);
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
