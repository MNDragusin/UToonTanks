// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank() : ABasePawn()
{
	LeftTrackMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left track"));
	LeftTrackMesh->SetupAttachment(BaseMesh);

	RightTrackMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right track"));
	RightTrackMesh->SetupAttachment(BaseMesh);
	
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
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	PlyerControllerRef = Cast<APlayerController>(GetController());
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(!PlyerControllerRef)
	{
		return;
	}
	
	FHitResult HitResult;
	if(!PlyerControllerRef->GetHitResultUnderCursor(ECC_Visibility,false, OUT HitResult))
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
