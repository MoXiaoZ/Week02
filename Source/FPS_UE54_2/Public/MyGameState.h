// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MyGameState.generated.h"

/**
 * 
 */
UCLASS()
class FPS_UE54_2_API AMyGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
    AMyGameState();

    /** 增加某个玩家的积分 */
    UFUNCTION(BlueprintCallable, Category = "Score")
    void AddPlayerScore(AMyPlayerState* PlayerState, int32 Points);

    /** 获取所有玩家的总积分 */
    UFUNCTION(BlueprintCallable, Category = "Score")
    int32 GetTotalScore() const;

    /** 输出所有玩家的积分和总积分 */
    UFUNCTION(BlueprintCallable, Category = "Score")
    void PrintScoreSummary() const;

    /** 全局积分，支持网络同步 */
    UPROPERTY(ReplicatedUsing = OnRep_TotalScore, VisibleAnywhere, BlueprintReadOnly, Category = "Score")
    int32 TotalScore;

    /** 玩家得分映射表 */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Score")
    TMap<AMyPlayerState*, int32> PlayerScores;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Rules")
    int32 NumberOfMyActor = 10;  // 目标数量

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Rules")
    int32 NumberOfImportantMyActor = 5;  // 目标数量

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Rules")
    float GameDuration = 25.0f;  // 游戏持续时间



    // 计算总得分
    void CalculateTotalScore();

    UFUNCTION(NetMulticast, Reliable)
    void MulticastPrintScores();


protected:
    virtual void BeginPlay() override;

    /** 当玩家分数改变时调用 */
    void UpdateTotalScore();

    /** 当 TotalScore 在客户端更新时触发 */
    UFUNCTION()
    void OnRep_TotalScore();
	
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    void SpawnMyActors();

    void EndGame();

};
