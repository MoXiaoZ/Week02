// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class FPS_UE54_2_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
    AMyGameModeBase();

    virtual void BeginPlay() override;
    //virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Rules")
    int32 NumberOfMyActor = 10;  // 生成的Actor总数量

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Rules")
    int32 NumberOfImportantMyActor = 5;  // 重要的Actor数量（重要的Actor得分翻倍）

    //UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Rules")
    //float GameDuration = 20.0f;  // 游戏持续时间

    

protected:
    /*UFUNCTION()
    void CountdownTick();

    UFUNCTION(NetMulticast, Reliable)
    void Multicast_UpdateTimeRemaining(int32 NewTime);

    UFUNCTION(NetMulticast, Reliable)
    void Multicast_EndGame();*/


private:
    void SpawnMyActors();
    //void EndGame();
    //FTimerHandle CountdownTimerHandle;
};
