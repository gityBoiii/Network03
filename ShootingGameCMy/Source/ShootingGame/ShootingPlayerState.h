// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "ShootingPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_API AShootingPlayerState : public APlayerState
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(ReplicatedUsing = OnRep_CurHP)
	float CurHP;
	
public:
	UFUNCTION()
	void OnRep_CurHP();
};
