// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"

#include "NavigationSystemTypes.h"
#include "Components/CapsuleComponent.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABasePawn::ABasePawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create CapsuleComp collider and make it the root component
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	//Create new static meshes for the base and attach it to the RootComponent
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	//Create new static meshes for the turret and attach it to the BaseMesh
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	//Create new static mehs afor the gun and attach it to the TurretMesh
	//GunMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunMesh"));
	//GunMesh->SetupAttachment(TurretMesh);

	//Create a spawn point of type USceneComponent and attach it to the Gun
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABasePawn::TurnTurret(FVector LookAtTarget)
{
	//Directional vector
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();

	//Create rotator and make make sure we only use the Yaw
	FRotator LookAtRotatation = ToTarget.Rotation();
	LookAtRotatation.Pitch = 0;
	LookAtRotatation.Roll = 0;

	TurretMesh->SetWorldRotation(LookAtRotatation, true);
}

void ABasePawn::Fire()
{
	if (!ProjectileClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s] - There is no projectile class assigned!"), *GetOwner()->GetName());
		return;
	}

	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass,
	                                                              ProjectileSpawnPoint->GetComponentLocation(),
	                                                              ProjectileSpawnPoint->GetComponentRotation());
	Projectile->SetOwner(this);
	
}

void ABasePawn::HandleDestruction()
{
	if(DestroyParticleSystem)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, DestroyParticleSystem, GetActorLocation(), GetActorRotation());	
	}
	
	//TODO Visual / sound effect
}
