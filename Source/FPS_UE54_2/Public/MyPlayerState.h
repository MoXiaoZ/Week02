// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MyPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class FPS_UE54_2_API AMyPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	AMyPlayerState();

	// ��ӻ���
	UFUNCTION(BlueprintCallable, Category = "Score")
	void AddScore(int32 Points);

	// ��ȡ��ҵ�ǰ����
	UFUNCTION(BlueprintCallable, Category = "Score")
	int32 GetCurrentScore() const;

protected:
	// ��ǰ���֣�֧������ͬ��
	UPROPERTY(ReplicatedUsing = OnRep_Score, VisibleAnywhere, BlueprintReadOnly, Category = "Score")
	int32 CurrentScore;

	// ����������ʱ����
	void OnRep_Score();
	
	
};
