// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SourceCollectHub.generated.h"

UCLASS()
class DRIVETOSURVIVE_API ASourceCollectHub : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere)
	TArray<int> CollectedSourceArray;
	
public:	
	// Sets default values for this actor's properties
	ASourceCollectHub();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void GetPlayerSource(TArray<int> PlayerTargetArray);
	void Read();
	void Save();
};
