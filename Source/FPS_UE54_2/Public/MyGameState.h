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

    /** ��ӡ������ҷ��� */
    void PrintAllPlayersScore();

    /** ȫ�ֻ��֣�֧������ͬ�� */
    UPROPERTY(ReplicatedUsing = OnRep_TotalScore, VisibleAnywhere, BlueprintReadOnly, Category = "Score")
    int32 TotalScore;

    //UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Rules")
    //int32 NumberOfMyActor = 10;  // ���ɵ�Actor������

    //UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Rules")
    //int32 NumberOfImportantMyActor = 5;  // ��Ҫ��Actor��������Ҫ��Actor�÷ַ�����

    //UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Rules")
    //float GameDuration = 25.0f;  // ��Ϸ����ʱ��


    // �����ܵ÷�
    void CalculateTotalScore();

    //UFUNCTION(NetMulticast, Reliable)
    //void MulticastPrintScores();


protected:
    virtual void BeginPlay() override;

    /** �� TotalScore �ڿͻ��˸���ʱ���� */
    UFUNCTION()
    void OnRep_TotalScore();
	
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    //void SpawnMyActors();

    //void EndGame();

};
