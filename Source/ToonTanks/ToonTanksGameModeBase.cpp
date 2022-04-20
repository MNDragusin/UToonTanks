// Copyright Epic Games, Inc. All Rights Reserved.


#include "ToonTanksGameModeBase.h"

#include "Kismet/GameplayStatics.h"
#include "ToonTanksPlayerController.h"
#include "Tank.h"
#include "Tower.h"

void AToonTanksGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	HandleGameStart();
}

void AToonTanksGameModeBase::HandleGameStart()
{
	TargetTowers = GetTargetTowerCount();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	
	StartGame();
	
	if (!ToonTanksPlayerController) return;

	ToonTanksPlayerController->SetPlayerEnableState(false);

	FTimerHandle PlayerEnableTimerHandle;
	FTimerDelegate InputDelegate = FTimerDelegate::CreateUObject(ToonTanksPlayerController,
	                                                             &AToonTanksPlayerController::SetPlayerEnableState,
	                                                             true);
	
	GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, InputDelegate, StartDelay, false);
}

int32 AToonTanksGameModeBase::GetTargetTowerCount() const
{
	TArray<AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), OUT Towers);
	
	return Towers.Num();
}

void AToonTanksGameModeBase::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();
		if (ToonTanksPlayerController)
		{
			ToonTanksPlayerController->SetPlayerEnableState(false);
		}

		GameOver(false);
	}
	else if (ATower* DestroydTower = Cast<ATower>(DeadActor))
	{
		DestroydTower->HandleDestruction();
		--TargetTowers;

		if(TargetTowers == 0)
		{
			GameOver(true);
		}
	}
}
