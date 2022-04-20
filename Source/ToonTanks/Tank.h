// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
public:
	ATank();
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void HandleDestruction();
	APlayerController* GetTankPlayerController() const;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
private:
	UPROPERTY(VisibleAnywhere, Category="Components")
	class UCameraComponent* CameraComponent;
	UPROPERTY(VisibleAnywhere, Category="Components")
	class USpringArmComponent* SpringArmComp;
		
	
	UPROPERTY(EditAnywhere, Category="Attributes")
	float MoveSpeed = 200.f;

	UPROPERTY(EditAnywhere, Category="Attributes")
	float RotateSpeed = 100.f;
	UPROPERTY(EditAnywhere, Category="Attributes")
	float TurretRotateSpeed = 50.f;
	
	void Move(float Value);
	void Turn(float Value);
	//members
	APlayerController* TankPlyerController;
};
