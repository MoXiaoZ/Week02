// Fill out your copyright notice in the Description page of Project Settings.


#include "MyUserWidget.h"
#include "Components/TextBlock.h"

void UMyUserWidget::UpdateCountdown(int32 NewTime)
{
    if (CountdownText)
    {
        // ��ʣ��ʱ�����Ϊ�ַ�����ʽ�����õ� TextBlock
        CountdownText->SetText(FText::FromString(FString::Printf(TEXT("%d"), NewTime)));
    }
}

//void UMyUserWidget::UpdateScoreList(FString StrScoreList)
//{
//    if (ScoreListText)
//    {
//        // ��ʣ��ʱ�����Ϊ�ַ�����ʽ�����õ� TextBlock
//        ScoreListText->SetText(FText::FromString(StrScoreList));
//    }
//}



