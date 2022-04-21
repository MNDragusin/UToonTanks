// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "../../Plugins/Developer/RiderLink/Source/RD/thirdparty/clsocket/src/ActiveSocket.h"
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

	if(!Tank->IsTankAlive())
	{
		return;
	}
	
	if(!IsTankInFireRange())
	{
		return;
	}

	if(!IsTankInLineOfSight())
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
	if(Tank == nullptr)
	{
		return;
	}
	
	if(Tank->IsTankAlive() && IsTankInFireRange() && IsTankInLineOfSight())
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

bool ATower::IsTankInLineOfSight()
{
	FHitResult HitResult;
	if(!GetWorld()->LineTraceSingleByChannel(OUT HitResult, GetActorLocation(), Tank->GetActorLocation(), ECC_Visibility))
	{
		return false;
	}

	return HitResult.GetActor() == Tank;
}
