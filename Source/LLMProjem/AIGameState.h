// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "AIGameState.generated.h"

/**
 *
 */
UCLASS()
class LLMPROJEM_API AAIGameState : public AGameStateBase // DÝKKAT: Burasý projenizin adýyla güncellenmiþ olabilir
{
	GENERATED_BODY()

public:
	/**
	 * This describes the setting of the game.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FText Setting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FString PlayerName;
};