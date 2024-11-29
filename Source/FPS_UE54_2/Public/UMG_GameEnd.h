// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UMG_GameEnd.generated.h"

/**
 * 
 */
UCLASS()
class FPS_UE54_2_API UUMG_GameEnd : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void UpdateScoreList(FString StrScoreList);

protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ScoreListText;
	
	
};
