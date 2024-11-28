// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerState.h"
#include "Net/UnrealNetwork.h"

AMyPlayerState::AMyPlayerState()
{
    // ��ʼ������
    CurrentScore = 0;
    bReplicates = true; // ��������ͬ��
    bAlwaysRelevant = true;
}

void AMyPlayerState::AddScore(int32 Points)
{
    //UE_LOG(LogTemp, Warning, TEXT("111"));
    if (HasAuthority()) // ���������˹���
    {
        CurrentScore += Points;

        // �ͻ��˴�ӡ���
        //OnRep_Score();
    }
    
    
}

int32 AMyPlayerState::GetCurrentScore() const
{
    return CurrentScore;
}

void AMyPlayerState::OnRep_Score()
{
    // �ڿͻ��˸���ʱ�����������߼���������� UI
    //GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, FString::Printf(TEXT("111%s:%d"), *GetPlayerName(), CurrentScore));
    //UE_LOG(LogTemp, Warning, TEXT("Player %s score updated: %d"), *GetPlayerName(), CurrentScore);
}

void AMyPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    // ������Ҫͬ���ı���
    DOREPLIFETIME(AMyPlayerState, CurrentScore); // ���Ʒ������ͻ���
}



