// Fill out your copyright notice in the Description page of Project Settings.


#include "MyUserWidget.h"
#include "Components/TextBlock.h"

void UMyUserWidget::UpdateCountdown(int32 NewTime)
{
    if (CountdownText)
    {
        // 将剩余时间更新为字符串格式并设置到 TextBlock
        CountdownText->SetText(FText::FromString(FString::Printf(TEXT("%d"), NewTime)));
    }
}

//void UMyUserWidget::UpdateScoreList(FString StrScoreList)
//{
//    if (ScoreListText)
//    {
//        // 将剩余时间更新为字符串格式并设置到 TextBlock
//        ScoreListText->SetText(FText::FromString(StrScoreList));
//    }
//}



