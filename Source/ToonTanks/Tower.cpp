// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(FireRateTimerHandle,this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(!IsTankInFireRange())
	{
		return;
	}

	TurnTurret(Tank->GetActorLocation());
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();

	Destroy();
}

void ATower::CheckFireCondition()
{
	if(IsTankInFireRange())
	{
		Fire();	
	}	
}

bool ATower::IsTankInFireRange()
{
	if(!Tank)
	{
		return false;
	}

	return FireRange >= FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
}
