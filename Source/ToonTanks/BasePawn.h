// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void TurnTurret(FVector LookAtTarget);
	void Fire();
	virtual void HandleDestruction();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components", meta= (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components", meta= (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComp;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components", meta= (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components", meta= (AllowPrivateAccess = "true"))
	UStaticMeshComponent* GunMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components", meta= (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category="Combat")
	UParticleSystem* DestroyParticleSystem;
	UPROPERTY(EditAnywhere, Category="Combat")
	UAudioComponent* FireAudioComp;
	UPROPERTY(EditAnywhere, Category="Combat")
	USoundBase* DeathSound;

	UPROPERTY(EditAnywhere, Category="Combat")
	TSubclassOf<UCameraShakeBase> DeathCameraShake;
};
