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

    /** 打印所有玩家分数 */
    void PrintAllPlayersScore();

    /** 全局积分，支持网络同步 */
    UPROPERTY(ReplicatedUsing = OnRep_TotalScore, VisibleAnywhere, BlueprintReadOnly, Category = "Score")
    int32 TotalScore;

    //UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Rules")
    //int32 NumberOfMyActor = 10;  // 生成的Actor总数量

    //UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Rules")
    //int32 NumberOfImportantMyActor = 5;  // 重要的Actor数量（重要的Actor得分翻倍）

    //UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Rules")
    //float GameDuration = 25.0f;  // 游戏持续时间


    // 计算总得分
    void CalculateTotalScore();

    //UFUNCTION(NetMulticast, Reliable)
    //void MulticastPrintScores();


protected:
    virtual void BeginPlay() override;

    /** 当 TotalScore 在客户端更新时触发 */
    UFUNCTION()
    void OnRep_TotalScore();
	
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    //void SpawnMyActors();

    //void EndGame();

};
