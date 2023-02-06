// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraComponent.h"
#include "PlayerCharater.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "Bomb.generated.h"

UCLASS()
class DRIVETOSURVIVE_API ABomb : public AActor
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	UNiagaraComponent* NiagaraComponent;
	UPROPERTY(EditAnywhere)
	USphereComponent* BoomSphereComponent;
	FTimerHandle Timer;
	void Finish();
	UPROPERTY(EditAnywhere)
	float ExitTime;
	UPROPERTY(EditAnywhere)
	float UpRate;

	float HurtValue;

	APlayerCharater* Character;
public:	
	// Sets default values for this actor's properties
	ABomb();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetBoomValue(float Value);
	
	UFUNCTION()
	virtual void OnOverlayBegin(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit);
};
