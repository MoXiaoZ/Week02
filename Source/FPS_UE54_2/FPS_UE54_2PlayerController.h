// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FPS_UE54_2PlayerController.generated.h"

class UInputMappingContext;

/**
 *
 */
UCLASS()
class FPS_UE54_2_API AFPS_UE54_2PlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	/** Input Mapping Context to be used for player input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	// Begin Actor interface
protected:

	virtual void BeginPlay() override;

	// �洢 Widget ��ʵ��
	UPROPERTY()
	class UMyUserWidget* MyWidget;

	UPROPERTY()
	class UUMG_GameEnd* MyGameEndUMG;

	// Widget ��
	UPROPERTY(EditDefaultsOnly, Category = "UI-Countdown")
	TSubclassOf<class UMyUserWidget> MyWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI-GameEnd")
	TSubclassOf<class UUMG_GameEnd> MyGameEndUMGClass;

public:
	// ���µ���ʱ
	void UpdateCountdown(int32 TimeRemaining);

	// ��Ϸ�������»��ֱ�
	void UpdateScoreList(FString ScoreList);

};
