// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "AirPlan.generated.h"

UCLASS()
class DRIVETOSURVIVE_API AAirPlan : public AActor
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	UBoxComponent* Box;
	UPROPERTY(EditAnywhere)
	FName SocketName;
public:	
	// Sets default values for this actor's properties
	AAirPlan();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bEnter;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USkeletalMeshComponent* MeshComponent;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnOverlayBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
							UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
							const FHitResult& SweepResult);

	UFUNCTION()
	virtual  void EndOverLap(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp);

	UFUNCTION(BlueprintImplementableEvent)
	void CPPStartFly();
};
