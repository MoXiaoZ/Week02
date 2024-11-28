// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerState.h"
#include "Net/UnrealNetwork.h"

AMyPlayerState::AMyPlayerState()
{
    // 初始化分数
    CurrentScore = 0;
    bReplicates = true; // 开启网络同步
    bAlwaysRelevant = true;
}

void AMyPlayerState::AddScore(int32 Points)
{
    //UE_LOG(LogTemp, Warning, TEXT("111"));
    if (HasAuthority()) // 仅服务器端管理
    {
        CurrentScore += Points;

        // 客户端打印输出
        //OnRep_Score();
    }
    
    
}

int32 AMyPlayerState::GetCurrentScore() const
{
    return CurrentScore;
}

void AMyPlayerState::OnRep_Score()
{
    // 在客户端更新时可以添加相关逻辑，比如更新 UI
    //GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, FString::Printf(TEXT("111%s:%d"), *GetPlayerName(), CurrentScore));
    //UE_LOG(LogTemp, Warning, TEXT("Player %s score updated: %d"), *GetPlayerName(), CurrentScore);
}

void AMyPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    // 声明需要同步的变量
    DOREPLIFETIME(AMyPlayerState, CurrentScore); // 复制分数到客户端
}



