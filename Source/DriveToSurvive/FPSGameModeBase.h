// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemy.h"
#include "GameFramework/GameModeBase.h"
#include "PlayerCharater.h"
#include "FPSGameModeBase.generated.h"
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerDiedSignature, ACharacter*, Character);
UCLASS()
class DRIVETOSURVIVE_API AFPSGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	bool bFinishTask;
	bool bBossKilled;
	void SaveGameMessage();
	void ReadGameMessage();
	UPROPERTY(EditAnywhere)
	int MaxEnemyNumber;

	FTimerHandle Timer;
	
	UPROPERTY(EditAnywhere)
	TArray<ABaseEnemy*> Enemies;

protected:
	virtual void BeginPlay() override;
public:
	UPROPERTY(EditAnywhere)
	int TotalTargetNum;
	UPROPERTY(EditAnywhere)
	TArray<int> TargetArray;
	AFPSGameModeBase();
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<APlayerCharater> Player;

	void RestartPlayer(AController* NewPlayer,FVector CurrentLocation);
	
	UFUNCTION()
	virtual void PlayerDied(ACharacter* Character);

	UPROPERTY()
	FOnPlayerDiedSignature OnPlayerDied;

	const FOnPlayerDiedSignature& GetOnPlayerDied() const { return OnPlayerDied; }

	void BossCreate();

	bool CanCreateEnemy();

	void AddEnemy(ABaseEnemy* Enemy);
};
