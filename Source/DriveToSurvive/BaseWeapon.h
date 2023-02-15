// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

UCLASS()
class DRIVETOSURVIVE_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	TArray<AActor*> Hit;
	UPROPERTY(EditAnywhere)
	TArray<FName> SocketNames;
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* MeshComponent;
	TArray<FVector> SocketLocation;
	bool bTrance;
	bool bFirst;
	void TranceSolution();
public:	
	// Sets default values for this actor's properties
	ABaseWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void LineTrancy();

	void Start();
	void End();
};
