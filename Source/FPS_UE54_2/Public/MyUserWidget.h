// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class FPS_UE54_2_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    // 更新倒计时文本
    UFUNCTION(BlueprintCallable)
    void UpdateCountdown(int32 NewTime);

    //UFUNCTION(BlueprintCallable)
    //void UpdateScoreList(FString StrScoreList);

protected:
    // 引用 TextBlock
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* CountdownText;

    //UPROPERTY(meta = (BindWidget))
    //class UTextBlock* ScoreListText;
	
	
};
