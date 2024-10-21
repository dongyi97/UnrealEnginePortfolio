// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
//#include "Components/Image.h"
//#include "Components/CanvasPanelSlot.h"
#include "WeaponUIManager.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UWeaponUIManager : public UUserWidget
{
	GENERATED_BODY()
	
public:
    UWeaponUIManager();



    // 이미지와 슬롯을 저장하는 변수들
    UPROPERTY(meta = (BindWidget))
    class UImage* Slot1Image;

    UPROPERTY(meta = (BindWidget))
    class UImage* Slot2Image;

    UPROPERTY(meta = (BindWidget))
    class UCanvasPanelSlot* Slot1Panel;

    UPROPERTY(meta = (BindWidget))
    class UCanvasPanelSlot* Slot2Panel;

    UPROPERTY(meta = (BindWidget))
    class UTexture2D* RifleImage;

    UPROPERTY(meta = (BindWidget))
    class UTexture2D* SniperImage;

    UPROPERTY(meta = (BindWidget))
    class UTexture2D* BazookaImage;

    void UpdateWeaponSlot(int32 SlotIndex, UTexture2D* WeaponImage);
    void SelectWeaponSlot(int32 SlotIndex);

};
