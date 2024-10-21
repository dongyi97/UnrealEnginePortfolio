// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WeaponUIManager.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"

void UWeaponUIManager::UpdateWeaponSlot(int32 SlotIndex, UTexture2D* WeaponImage)
{
    FSlateBrush Brush;
    Brush.SetResourceObject(WeaponImage);  // 이미지 설정

    if (SlotIndex == 0)
    {
        Slot1Image->SetBrush(Brush);
    }
    else if (SlotIndex == 1)
    {
        Slot2Image->SetBrush(Brush);
    }
}

void UWeaponUIManager::SelectWeaponSlot(int32 SlotIndex)
{
    FVector2D SelectedSize = FVector2D(150.0f, 150.0f); // 선택된 슬롯 크기
    FVector2D NormalSize = FVector2D(100.0f, 100.0f);   // 일반 슬롯 크기

    if (SlotIndex == 1)
    {
        Slot1Panel->SetSize(SelectedSize);
        Slot2Panel->SetSize(NormalSize);
    }
    else if (SlotIndex == 2)
    {
        Slot1Panel->SetSize(NormalSize);
        Slot2Panel->SetSize(SelectedSize);
    }
}
