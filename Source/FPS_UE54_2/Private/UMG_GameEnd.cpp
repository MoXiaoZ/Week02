// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG_GameEnd.h"
#include "Components/TextBlock.h"

void UUMG_GameEnd::UpdateScoreList(FString StrScoreList)
{
    if (ScoreListText)
    {
        // ��ʣ��ʱ�����Ϊ�ַ�����ʽ�����õ� TextBlock
        ScoreListText->SetText(FText::FromString(StrScoreList));
    }
}


