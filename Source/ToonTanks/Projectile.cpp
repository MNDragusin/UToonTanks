// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "Components/AudioComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;
		
	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile movement comp"));
	ProjectileMovementComp->MaxSpeed = 6000.f;
	ProjectileMovementComp->InitialSpeed = 5000.f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	auto MyOwner = GetOwner();

	if(MyOwner== nullptr) return;
	auto myOwnerInstigator = MyOwner->GetInstigatorController();
	auto DamageTypeClass = UDamageType::StaticClass();

	if(!OtherActor && OtherActor == this && OtherActor == MyOwner)
	{
		return;
	}
	
	UGameplayStatics::ApplyDamage(OtherActor, Damage, myOwnerInstigator, this,DamageTypeClass);
	UGameplayStatics::SpawnEmitterAtLocation(this, HitPArticles, GetActorLocation(), GetActorRotation());

	if(ImpactSound != nullptr)
	{
		UGameplayStatics::SpawnSoundAtLocation(this, ImpactSound, GetActorLocation(),GetActorRotation());	
	}

	if(CameraShakeClass != nullptr)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(CameraShakeClass);
	}
	
	//Destroy projectile
	Destroy();
}

