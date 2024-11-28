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
    bReplicates = true; // ��������ͬ��
}

void AMyGameState::BeginPlay()
{
    SpawnMyActors();

    if (!HasAuthority()) {
        
    }
    FTimerHandle TimerHandle;// ���嶨ʱ��
    // ���� GameDuration ������ EndGameCallback ����
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AMyGameState::EndGame, GameDuration, false);
        
}

void AMyGameState::SpawnMyActors()
{
    if (!HasAuthority()) // ȷ��ֻ�ڷ�����������
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
                // �ڷǹ��캯����ʹ��StaticLoadObject�����ʲ�����FObjectFinder�ᱨ��
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

void AMyGameState::AddPlayerScore(AMyPlayerState* PlayerState, int32 Points)
{
    if (!PlayerState) return;

    if (!HasAuthority()) return;// ���������˹���

    // ������һ���ӳ��
    if (PlayerScores.Contains(PlayerState))
    {
        PlayerScores[PlayerState] += Points;
    }
    else
    {
        PlayerScores.Add(PlayerState, Points);
    }

    // �����ܻ���
    UpdateTotalScore();
}

int32 AMyGameState::GetTotalScore() const
{
    return TotalScore;
}

void AMyGameState::PrintScoreSummary() const
{
    UE_LOG(LogTemp, Log, TEXT("------ Score Summary ------"));
    for (const TPair<AMyPlayerState*, int32>& PlayerScore : PlayerScores)
    {
        if (PlayerScore.Key)
        {
            UE_LOG(LogTemp, Warning, TEXT("Player %s: %d Points"), *PlayerScore.Key->GetPlayerName(), PlayerScore.Value);
        }
    }
    UE_LOG(LogTemp, Warning, TEXT("Total Score: %d"), TotalScore);
}

void AMyGameState::UpdateTotalScore()
{
    if (!HasAuthority()) return;// ���������˹���
    TotalScore = 0;

    for (APlayerState* PlayerState : PlayerArray)
    {
        if (AMyPlayerState* MyPlayerState = Cast<AMyPlayerState>(PlayerState))
        {
            TotalScore += MyPlayerState->GetCurrentScore();
            GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, FString::Printf(TEXT("Player %s Score: %d"),
                *MyPlayerState->GetPlayerName(),
                MyPlayerState->GetCurrentScore()));
            /*UE_LOG(LogTemp, Warning, TEXT("Player %s Score: %d"),
                *MyPlayerState->GetPlayerName(),
                MyPlayerState->GetCurrentScore());*/

            //GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, FString::Printf(TEXT("%s:%d"), *MyPlayerState->GetPlayerName(), MyPlayerState->GetCurrentScore()));

        }
    }
    GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, FString::Printf(TEXT("total:%d"), TotalScore));
}

void AMyGameState::OnRep_TotalScore()
{
    // �ͻ����յ� TotalScore ����ʱ�����Դ��� UI �������߼�
    UE_LOG(LogTemp, Log, TEXT("Total score replicated: %d"), TotalScore);
}

void AMyGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    // ������Ҫͬ���ı���
    DOREPLIFETIME(AMyGameState, TotalScore);
}

void AMyGameState::EndGame()
{
    if (!HasAuthority()) return;

    CalculateTotalScore();

    //for (APlayerState* PlayerState : PlayerArray)
    //{
    //    if (AMyPlayerState* MyPlayerState = Cast<AMyPlayerState>(PlayerState))
    //    {
    //        FString psPrint = FString::Printf(TEXT("Player %s Score: %d"), 
    //            *MyPlayerState->GetPlayerName(),
    //            MyPlayerState->GetCurrentScore());
    //        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, psPrint);
    //        UE_LOG(LogTemp, Warning, TEXT("Player %s Score: %d"),
    //            *MyPlayerState->GetPlayerName(),
    //            MyPlayerState->GetCurrentScore());
    //    }
    //}
    //FString totalPrint = FString::Printf(TEXT("Total Score: %d"), TotalScore);
    //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, totalPrint);
    //UE_LOG(LogTemp, Log, TEXT("Total Score: %d"), TotalScore);

    // �㲥���ͻ���
    MulticastPrintScores();

    //AMyGameState* MyGameStateObject = GetWorld()->GetGameState<AMyGameState>();
    //// ����ת��Ϊ MyGameState
    //if (MyGameStateObject)
    //{
    //    MyGameStateObject->PrintScoreSummary();
    //}
    //else
    //{
    //    UE_LOG(LogTemp, Warning, TEXT("GameStateBase is null."));
    //}
    
}

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

void AMyGameState::MulticastPrintScores_Implementation()
{
    if (HasAuthority()) return;//�ڿͻ���ִ��

    for (APlayerState* PlayerState : PlayerArray)
    {
        if (AMyPlayerState* MyPlayerState = Cast<AMyPlayerState>(PlayerState))
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Player %s Score: %d"),
                *MyPlayerState->GetPlayerName(),
                MyPlayerState->GetCurrentScore()));
            /*UE_LOG(LogTemp, Warning, TEXT("Player %s Score: %d"),
                *MyPlayerState->GetPlayerName(),
                MyPlayerState->GetCurrentScore());*/
        }
    }
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Total Score on Client: %d"), TotalScore));

    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Game Over! ")));
}



