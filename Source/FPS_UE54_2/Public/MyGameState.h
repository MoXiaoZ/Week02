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

    /** ����ĳ����ҵĻ��� */
    UFUNCTION(BlueprintCallable, Category = "Score")
    void AddPlayerScore(AMyPlayerState* PlayerState, int32 Points);

    /** ��ȡ������ҵ��ܻ��� */
    UFUNCTION(BlueprintCallable, Category = "Score")
    int32 GetTotalScore() const;

    /** ���������ҵĻ��ֺ��ܻ��� */
    UFUNCTION(BlueprintCallable, Category = "Score")
    void PrintScoreSummary() const;

    /** ȫ�ֻ��֣�֧������ͬ�� */
    UPROPERTY(ReplicatedUsing = OnRep_TotalScore, VisibleAnywhere, BlueprintReadOnly, Category = "Score")
    int32 TotalScore;

    /** ��ҵ÷�ӳ��� */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Score")
    TMap<AMyPlayerState*, int32> PlayerScores;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Rules")
    int32 NumberOfMyActor = 10;  // Ŀ������

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Rules")
    int32 NumberOfImportantMyActor = 5;  // Ŀ������

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Rules")
    float GameDuration = 25.0f;  // ��Ϸ����ʱ��



    // �����ܵ÷�
    void CalculateTotalScore();

    UFUNCTION(NetMulticast, Reliable)
    void MulticastPrintScores();


protected:
    virtual void BeginPlay() override;

    /** ����ҷ����ı�ʱ���� */
    void UpdateTotalScore();

    /** �� TotalScore �ڿͻ��˸���ʱ���� */
    UFUNCTION()
    void OnRep_TotalScore();
	
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    void SpawnMyActors();

    void EndGame();

};
