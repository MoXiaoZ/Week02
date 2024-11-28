// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MyPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class FPS_UE54_2_API AMyPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	AMyPlayerState();

	// 添加积分
	UFUNCTION(BlueprintCallable, Category = "Score")
	void AddScore(int32 Points);

	// 获取玩家当前积分
	UFUNCTION(BlueprintCallable, Category = "Score")
	int32 GetCurrentScore() const;

protected:
	// 当前积分，支持网络同步
	UPROPERTY(ReplicatedUsing = OnRep_Score, VisibleAnywhere, BlueprintReadOnly, Category = "Score")
	int32 CurrentScore;

	// 当分数更新时触发
	void OnRep_Score();
	
	
};
