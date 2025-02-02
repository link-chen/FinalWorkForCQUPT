// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWeapon.h"
#include "GameFramework/Character.h"
#include "BaseEnemy.generated.h"

UCLASS()
class DRIVETOSURVIVE_API ABaseEnemy : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float MaxLife;
	float CurrentLife;

	UPROPERTY(EditAnywhere)
	UAnimMontage* DeathMontage;
	UPROPERTY(EditAnywhere)
	UAnimMontage* HurtMontage;

	UPROPERTY()
	bool bFindEnemy;
	

	void DieOut();

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseWeapon> BaseWeapon;

	UPROPERTY(EditAnywhere)
	FVector Location;
	UPROPERTY(EditAnywhere)
	FRotator Rotation;
	
public:
	// Sets default values for this character's properties
	ABaseEnemy();

	ABaseWeapon* Weapon;
	
	UPROPERTY(EditAnywhere)
	float DeleteTime;

	virtual void PlayDeathAnimation();

	UPROPERTY(BlueprintReadWrite)
	bool bLive;

	UFUNCTION(BlueprintCallable)
	virtual void Death();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	FTimerHandle DeleteHandle;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetHurt(float Value);
	UFUNCTION(BlueprintCallable)
	virtual float GetCurrentPercent();

	UPROPERTY(EditAnywhere)
	FString EnemyLable;

	UFUNCTION(BlueprintCallable)
	void HitStart();
	UFUNCTION(BlueprintCallable)
	void HitEnd();
};
