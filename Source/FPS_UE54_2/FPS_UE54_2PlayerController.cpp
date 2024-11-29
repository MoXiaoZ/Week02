// Copyright Epic Games, Inc. All Rights Reserved.


#include "FPS_UE54_2PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "MyHUD.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.h"
#include "MyPlayerState.h"
#include "UMG_GameEnd.h"

void AFPS_UE54_2PlayerController::BeginPlay()
{
	Super::BeginPlay();

	// get the enhanced input subsystem
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
	
	
	if (IsLocalController()) {//本地控制器才能更新Widget
		if (MyWidgetClass)
		{
			// 创建 Widget 并添加到屏幕
			MyWidget = CreateWidget<UMyUserWidget>(this, MyWidgetClass);
			if (MyWidget)
			{
				MyWidget->AddToViewport();
			}
		}
	}
	
	
}

void AFPS_UE54_2PlayerController::UpdateCountdown(int32 TimeRemaining)
{
	/*APlayerState* MyPlayerState = PlayerState;
	AMyPlayerState* pc = Cast<AMyPlayerState>(MyPlayerState);
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Black, FString::Printf(TEXT("Player %s,time:%d"), *(pc->GetPlayerName()), TimeRemaining));*/
	
	if (IsLocalController()&& MyWidget)
	{
		MyWidget->UpdateCountdown(TimeRemaining);
	}
}

void AFPS_UE54_2PlayerController::UpdateScoreList(FString ScoreList)
{
	/*APlayerState* MyPlayerState = PlayerState;
	AMyPlayerState* pc = Cast<AMyPlayerState>(MyPlayerState);
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Black, FString::Printf(TEXT("Player %s,time:%d"), *(pc->GetPlayerName()), TimeRemaining));*/

	if (IsLocalController())
	{
		if (MyGameEndUMGClass) {
			MyGameEndUMG = CreateWidget<UUMG_GameEnd>(this, MyGameEndUMGClass);
			if (MyGameEndUMG)
			{
				MyGameEndUMG->AddToViewport();
			}
			MyGameEndUMG->UpdateScoreList(ScoreList);
		}
		
	}
}