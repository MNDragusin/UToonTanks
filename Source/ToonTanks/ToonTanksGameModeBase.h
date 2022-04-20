// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	void ActorDied(AActor* DeadActor);

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);
	
private:

	void HandleGameStart();
	
	//members
	class ATank* Tank;
	class AToonTanksPlayerController* ToonTanksPlayerController;

	UPROPERTY(EditAnywhere)
	float StartDelay =3.f;

	int32 TargetTowers = 0;
	int32 GetTargetTowerCount() const;
};
