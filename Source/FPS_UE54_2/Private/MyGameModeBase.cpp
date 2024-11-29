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

AMyGameModeBase::AMyGameModeBase()
{
    PrimaryActorTick.bCanEverTick = true;
    PlayerStateClass = AMyPlayerState::StaticClass();
    GameStateClass = AMyGameState::StaticClass();
    PlayerControllerClass = AFPS_UE54_2PlayerController::StaticClass();
}

void AMyGameModeBase::BeginPlay()
{       
    FTimerHandle TimerHandle;// 定义定时器
    // 设置 GameDuration 秒后调用 EndGameCallback 函数
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AMyGameModeBase::EndGame, GameDuration, false);

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

void AMyGameModeBase::EndGame()
{   
    if (!HasAuthority()) return;
    AMyGameState* MyGameStateObject = GetWorld()->GetGameState<AMyGameState>();
    // 将其转换为 MyGameState
    if (MyGameStateObject)
    {
        MyGameStateObject->CalculateTotalScore();
        for (APlayerState* PlayerState : MyGameStateObject->PlayerArray)
        {
            if (AMyPlayerState* MyPlayerState = Cast<AMyPlayerState>(PlayerState))
            {
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Player %s Score: %d"),
                    *MyPlayerState->GetPlayerName(),
                    MyPlayerState->GetCurrentScore()));
            }
        }
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Total Score: %d"), MyGameStateObject->TotalScore));

        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Game Over! ")));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("GameStateBase is null."));
    }

    
}



