// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
public:
	virtual void Tick(float DeltaTime) override;
	void HandleDestruction();
	
private:
	void CheckFireCondition();
	bool IsTankInFireRange();
	bool IsTankInLineOfSight();
	//members
	class ATank* Tank;
	FTimerHandle FireRateTimerHandle;

	UPROPERTY(EditAnywhere, Category="Attributes")
	float FireRange = 200.f;

	UPROPERTY(EditAnywhere, Category="Attributes")
	float FireRate = 2.f;
};
