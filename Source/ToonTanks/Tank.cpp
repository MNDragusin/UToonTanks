// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "Camera/CameraComponent.h"
#include "Camera/CameraShakeSourceComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank() : ABasePawn()
{
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComp);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);

	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

void ATank::HandleDestruction()
{	
	Super::HandleDestruction();
	bIsAlive = false;
	
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}

APlayerController* ATank::GetTankPlayerController() const
{
	return TankPlyerController;
}

bool ATank::IsTankAlive()
{
	return bIsAlive;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	TankPlyerController = Cast<APlayerController>(GetController());
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!TankPlyerController)
	{
		return;
	}

	FHitResult HitResult;
	if (!TankPlyerController->GetHitResultUnderCursor(ECC_Visibility, false, OUT HitResult))
	{
		return;
	}

	TurnTurret(HitResult.ImpactPoint);
	DrawDebugSphere(
		GetWorld(),
		HitResult.ImpactPoint,
		8.f,
		8,
		FColor::Red,
		false
	);
}

void ATank::Move(float Value)
{
	FVector DeltaLocation(0.f);
	DeltaLocation.X = Value * MoveSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(float Value)
{
	FRotator DeltaRotation = FRotator::ZeroRotator;
	DeltaRotation.Yaw = Value * RotateSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalRotation(DeltaRotation, true);
}
