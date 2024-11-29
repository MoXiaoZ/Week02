// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG_GameEnd.h"
#include "Components/TextBlock.h"

void UUMG_GameEnd::UpdateScoreList(FString StrScoreList)
{
    if (ScoreListText)
    {
        // 将剩余时间更新为字符串格式并设置到 TextBlock
        ScoreListText->SetText(FText::FromString(StrScoreList));
    }
}


