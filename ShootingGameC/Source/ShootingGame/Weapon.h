// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponInterface.h"
#include "GameFramework/Actor.h"
#include "Net/UnrealNetwork.h"
#include "Weapon.generated.h"

UCLASS()
class SHOOTINGGAME_API AWeapon : public AActor, public IWeaponInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void PressTrigger();

	virtual void PressTrigger_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void NotifyShoot();

	virtual void NotifyShoot_Implementation() override;

public:
	UFUNCTION(Server, Reliable)
	void ReqShoot(const FVector vStart, const FVector vEnd);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;

	UPROPERTY(Replicated, BlueprintReadWrite, Meta = (ExposeOnSpawn = "true"))
	ACharacter* OwnChar;

	UPROPERTY(Replicated, BlueprintReadWrite, Meta = (ExposeOnSpawn = "true"))
	UAnimMontage* AnimMontage_Shoot;

	UPROPERTY(Replicated, BlueprintReadWrite, Meta = (ExposeOnSpawn = "true"))
	UParticleSystem* FireEffect;
};
