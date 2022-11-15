// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	RootComponent = Mesh;
	
	bReplicates = true;
	SetReplicateMovement(true);
	bNetUseOwnerRelevancy = true;
	
}

void AWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AWeapon, OwnChar);
	DOREPLIFETIME(AWeapon, AnimMontage_Shoot);
	DOREPLIFETIME(AWeapon, FireEffect);
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::PressTrigger_Implementation()
{
	OwnChar->PlayAnimMontage(AnimMontage_Shoot);
}

void AWeapon::NotifyShoot_Implementation()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FireEffect, Mesh->GetSocketLocation("Muzzle"), Mesh->GetSocketRotation("Muzzle"), FVector(0.3f, 0.3f, 0.3f));

	APlayerController* shooter = GetWorld()->GetFirstPlayerController();
	if (GetWorld()->GetFirstPlayerController() == OwnChar->GetController())
	{
		FVector forward = shooter->PlayerCameraManager->GetActorForwardVector();
		FVector start = (forward * 350.0f) + shooter->PlayerCameraManager->GetCameraLocation();
		FVector end = start + (forward * 5000.0f);
		
		ReqShoot(start, end);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Client - Hit")));

	}
}

void AWeapon::ReqShoot_Implementation(const FVector vStart, const FVector vEnd)
{
	FHitResult result;
	bool isHit = GetWorld()->LineTraceSingleByObjectType(result, vStart, vEnd, ECollisionChannel::ECC_Pawn);

	DrawDebugLine(GetWorld(), vStart, vEnd, FColor::Yellow, false, 5.0f);

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Server - ReqShoot")));
	
	if (isHit)
	{
		ACharacter* HitChar = Cast<ACharacter>(result.GetActor());
		if (result.GetActor())
		{
			UGameplayStatics::ApplyDamage(HitChar, 10.0f, 
				OwnChar->GetController(), this, UDamageType::StaticClass());
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Server - Hit")));
		}
	}
}

