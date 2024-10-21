// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCamera.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>

UPlayerCamera::UPlayerCamera()
{
	
}

void UPlayerCamera::SetupInputBinding(UEnhancedInputComponent* PlayerInput)
{
	PlayerInput->BindAction(ia_LookAround, ETriggerEvent::Started, this, &UPlayerCamera::LookAround);
	PlayerInput->BindAction(ia_LookAround, ETriggerEvent::Completed, this, &UPlayerCamera::LookAround);
	PlayerInput->BindAction(ia_CameraSwitch, ETriggerEvent::Started, this, &UPlayerCamera::CameraSwitch);

	// 기울기 입력 바인딩
	PlayerInput->BindAction(ia_LeanLeft, ETriggerEvent::Started, this, &UPlayerCamera::BeginLeanLeft);
	PlayerInput->BindAction(ia_LeanLeft, ETriggerEvent::Completed, this, &UPlayerCamera::EndLean);
	PlayerInput->BindAction(ia_LeanRight, ETriggerEvent::Started, this, &UPlayerCamera::BeginLeanRight);
	PlayerInput->BindAction(ia_LeanRight, ETriggerEvent::Completed, this, &UPlayerCamera::EndLean);
}

void UPlayerCamera::LookAround(const FInputActionValue& inputValue)
{
	if (me->bUseControllerRotationYaw)
	{
		me->bUseControllerRotationYaw = false; // bUseControllerRotationYaw를 꺼줘서 주변 시야를 둘러 볼 수 있게 한다.
		me->GetCharacterMovement()->bOrientRotationToMovement = true;
	}
	else
	{
		me->bUseControllerRotationYaw = true;
		me->GetCharacterMovement()->bOrientRotationToMovement = false;
		if (APlayerController* PC = Cast<APlayerController>(me->GetController()))
		{
			FRotator CharacterRotation = me->GetActorRotation();
			PC->SetControlRotation(CharacterRotation);
			//bIsResettingCamera = true;
		}
	}
}

void UPlayerCamera::CameraSwitch(const FInputActionValue& inputValue)
{
	if (me->bIsTPS == true) // 현재 3인칭 시점일 때 1인칭을 바꿔준다
	{
		me->bIsTPS = false;
		me->tpsCamComp->SetActive(false);
		me->fpsCamComp->SetActive(true);
		me->GetMesh()->SetOwnerNoSee(true); // 1인칭일 때 메시 안 보이도록
	}
	else // 현재 1인칭 시점일 떄
	{
		me->bIsTPS = true;
		me->tpsCamComp->SetActive(true);
		me->fpsCamComp->SetActive(false);
		me->GetMesh()->SetOwnerNoSee(false);
	}
}

void UPlayerCamera::BeginLeanLeft()
{
	me->TargetLeanAngle = -15.0f; // 좌측으로 15도 기울기
}

void UPlayerCamera::BeginLeanRight()
{
	me->TargetLeanAngle = 15.0f; // 우측으로 15도 기울기
}

void UPlayerCamera::EndLean()
{
	me->TargetLeanAngle = 0.0f; // 기울기 초기화
}