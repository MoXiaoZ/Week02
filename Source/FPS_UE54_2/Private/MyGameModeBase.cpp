// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MyActor.h"
#include "GameFramework/PlayerState.h"
#include "Engine/World.h"
#include "MyGameState.h"
#include "MyPlayerState.h"
#include "../FPS_UE54_2PlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInstanceConstant.h"
#include "TimerManager.h"
#include "MyHUD.h"

AMyGameModeBase::AMyGameModeBase()
{
    PrimaryActorTick.bCanEverTick = true;
    PlayerStateClass = AMyPlayerState::StaticClass();
    GameStateClass = AMyGameState::StaticClass();
    PlayerControllerClass = AFPS_UE54_2PlayerController::StaticClass();
    //HUDClass = AMyHUD::StaticClass();
}

void AMyGameModeBase::BeginPlay()
{       
    //FTimerHandle TimerHandle;// 定义定时器
    //// 设置 GameDuration 秒后调用 EndGameCallback 函数
    //GetWorld()->GetTimerManager().SetTimer(CountdownTimerHandle, this, &AMyGameModeBase::CountdownTick, 1.0f, true);

    SpawnMyActors();
}


void AMyGameModeBase::SpawnMyActors()
{
    if (!HasAuthority()) // 确保只在服务器端运行
    {
        return;
    }

    int32 index = 1;
    for (int32 i = 0; i < NumberOfMyActor; ++i)
    {
        FVector Location = FVector(FMath::RandRange(150, 2850), FMath::RandRange(150, 3350), 50.062593);
        FRotator Rotation = FRotator::ZeroRotator;

        AMyActor* Target = GetWorld()->SpawnActor<AMyActor>(AMyActor::StaticClass(), Location, Rotation);
        if (Target)
        {
            if (index <= NumberOfImportantMyActor) {

                Target->isImportantTarget = true;
                // 在非构造函数中使用StaticLoadObject加载资产，用FObjectFinder会报错
                UMaterialInstanceConstant* MaterialAsset = Cast<UMaterialInstanceConstant>(
                    StaticLoadObject(UMaterialInstanceConstant::StaticClass(), nullptr, TEXT("/Game/LevelPrototyping/Materials/MI_Solid_Red.MI_Solid_Red"))
                );
                if (MaterialAsset)
                {
                    // Set the material on the static mesh component
                    Target->StaticMeshComp->SetMaterial(0, MaterialAsset);
                }
                else
                {
                    UE_LOG(LogTemp, Warning, TEXT("Material instance not found!"));
                }
            }
            ++index;
        }
    }
}

//void AMyGameModeBase::CountdownTick()
//{
//    // Decrease the remaining time
//    GameDuration--;
//
//    // Notify clients of the updated time
//    Multicast_UpdateTimeRemaining(GameDuration);
//
//    // If the time is up, end the game
//    if (GameDuration <= 0)
//    {
//        GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
//        Multicast_EndGame();
//    }
//}
//
//void AMyGameModeBase::Multicast_UpdateTimeRemaining_Implementation(int32 NewTime)
//{
//    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
//    {
//        APlayerController* PC = It->Get();
//        if (PC)
//        {
//            AFPS_UE54_2PlayerController* MyPC = Cast<AFPS_UE54_2PlayerController>(PC);
//            if (MyPC)
//            {
//                //GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Black, FString::Printf(TEXT("Player %s"), *(PC->PlayerState->GetPlayerName())));
//                MyPC->UpdateCountdown(NewTime); // 更新客户端的倒计时
//                /*APlayerState* PS = MyPC->PlayerState;
//                if (PS)
//                {
//                    AMyPlayerState* MyPS = Cast<AMyPlayerState>(PS);
//                    MyPS->rtime = NewTime;
//                }*/
//            }
//        }
//    }
//
//    //for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
//    //{
//    //    APlayerController* PC = It->Get();
//    //    if (PC)
//    //    {
//    //        
//    //        AMyHUD* HUD = Cast<AMyHUD>(PC->GetHUD());
//    //        if (HUD)
//    //        {
//    //            GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Black, FString::Printf(TEXT("Player %s"), *(PC->PlayerState->GetPlayerName())));
//    //            HUD->UpdateCountdown(NewTime);
//    //        }
//    //    }
//    //}
//}
//
//void AMyGameModeBase::Multicast_EndGame_Implementation()
//{
//    // Notify all clients that the game has ended
//    // Implement your game-ending logic here
//}
//
//void AMyGameModeBase::EndGame()
//{   
//    if (!HasAuthority()) return;
//    AMyGameState* MyGameStateObject = GetWorld()->GetGameState<AMyGameState>();
//    // 将其转换为 MyGameState
//    if (MyGameStateObject)
//    {
//        MyGameStateObject->CalculateTotalScore();
//        for (APlayerState* PlayerState : MyGameStateObject->PlayerArray)
//        {
//            if (AMyPlayerState* MyPlayerState = Cast<AMyPlayerState>(PlayerState))
//            {
//                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Player %s Score: %d"),
//                    *MyPlayerState->GetPlayerName(),
//                    MyPlayerState->GetCurrentScore()));
//            }
//        }
//        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Total Score: %d"), MyGameStateObject->TotalScore));
//
//        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Game Over! ")));
//    }
//    else
//    {
//        UE_LOG(LogTemp, Warning, TEXT("GameStateBase is null."));
//    }
//
//    
//}



