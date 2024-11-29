// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameState.h"
#include "Net/UnrealNetwork.h"
#include "MyPlayerState.h"
#include "Engine/World.h"
#include "MyActor.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInstanceConstant.h"
#include "GameFramework/PlayerState.h"
#include "../FPS_UE54_2PlayerController.h"
#include "TimerManager.h"

AMyGameState::AMyGameState()
{
    TotalScore = 0;
    bReplicates = true; // 启用网络同步
}

void AMyGameState::BeginPlay()
{
    //SpawnMyActors();

    //if (!HasAuthority()) {
    //    
    //}
    //FTimerHandle TimerHandle;// 定义定时器
    //// 设置 GameDuration 秒后调用 EndGameCallback 函数
    //GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AMyGameState::EndGame, GameDuration, false);
        
}

//void AMyGameState::SpawnMyActors()
//{
//    if (!HasAuthority()) // 确保只在服务器端运行
//    {
//        return;
//    }
//    int32 index = 1;
//    for (int32 i = 0; i < NumberOfMyActor; ++i)
//    {
//        FVector Location = FVector(FMath::RandRange(150, 2850), FMath::RandRange(150, 3350), 50.062593);
//        FRotator Rotation = FRotator::ZeroRotator;
//
//        AMyActor* Target = GetWorld()->SpawnActor<AMyActor>(AMyActor::StaticClass(), Location, Rotation);
//        if (Target)
//        {
//            if (index <= NumberOfImportantMyActor) {
//
//                Target->isImportantTarget = true;
//                // 在非构造函数中使用StaticLoadObject加载资产，用FObjectFinder会报错
//                UMaterialInstanceConstant* MaterialAsset = Cast<UMaterialInstanceConstant>(
//                    StaticLoadObject(UMaterialInstanceConstant::StaticClass(), nullptr, TEXT("/Game/LevelPrototyping/Materials/MI_Solid_Red.MI_Solid_Red"))
//                );
//                if (MaterialAsset)
//                {
//                    // Set the material on the static mesh component
//                    Target->StaticMeshComp->SetMaterial(0, MaterialAsset);
//                }
//                else
//                {
//                    UE_LOG(LogTemp, Warning, TEXT("Material instance not found!"));
//                }
//            }
//            ++index;
//        }
//    }
//}


void AMyGameState::PrintAllPlayersScore()
{
    if (!HasAuthority()) return;// 仅服务器端管理
    //TotalScore = 0;

    for (APlayerState* PlayerState : PlayerArray)
    {
        if (AMyPlayerState* MyPlayerState = Cast<AMyPlayerState>(PlayerState))
        {
            //TotalScore += MyPlayerState->GetCurrentScore();
            GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, FString::Printf(TEXT("Player %s Score: %d"),
                *MyPlayerState->GetPlayerName(),
                MyPlayerState->GetCurrentScore()));            
        }
    }
    //GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, FString::Printf(TEXT("total:%d"), TotalScore));
}

void AMyGameState::OnRep_TotalScore()
{
    UE_LOG(LogTemp, Log, TEXT("Total score replicated: %d"), TotalScore);
}

void AMyGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    // 声明需要同步的变量
    DOREPLIFETIME(AMyGameState, TotalScore);
}

//void AMyGameState::EndGame()
//{
//    if (!HasAuthority()) return;
//
//    CalculateTotalScore();
//    
//    for (APlayerState* PlayerState : PlayerArray)
//    {
//        if (AMyPlayerState* MyPlayerState = Cast<AMyPlayerState>(PlayerState))
//        {
//            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Player %s Score: %d"),
//                *MyPlayerState->GetPlayerName(),
//                MyPlayerState->GetCurrentScore()));
//        }
//    }
//    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Total Score: %d"), TotalScore));
//
//    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Game Over! ")));
//    // 广播到客户端
//    //MulticastPrintScores();
//    
//}

void AMyGameState::CalculateTotalScore()
{
    if (!HasAuthority()) return;

    TotalScore = 0;
    for (APlayerState* PlayerState : PlayerArray)
    {
        if (AMyPlayerState* MyPlayerState = Cast<AMyPlayerState>(PlayerState))
        {
            TotalScore += MyPlayerState->GetCurrentScore();
        }
    }

}

//void AMyGameState::MulticastPrintScores_Implementation()
//{
//    if (HasAuthority()) return;//在客户端执行
//
//    for (APlayerState* PlayerState : PlayerArray)
//    {
//        if (AMyPlayerState* MyPlayerState = Cast<AMyPlayerState>(PlayerState))
//        {
//            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Player %s Score: %d"),
//                *MyPlayerState->GetPlayerName(),
//                MyPlayerState->GetCurrentScore()));
//            /*UE_LOG(LogTemp, Warning, TEXT("Player %s Score: %d"),
//                *MyPlayerState->GetPlayerName(),
//                MyPlayerState->GetCurrentScore());*/
//        }
//    }
//    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Total Score on Client: %d"), TotalScore));
//
//    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Game Over! ")));
//}




