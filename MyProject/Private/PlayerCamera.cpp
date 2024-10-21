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

	// ���� �Է� ���ε�
	PlayerInput->BindAction(ia_LeanLeft, ETriggerEvent::Started, this, &UPlayerCamera::BeginLeanLeft);
	PlayerInput->BindAction(ia_LeanLeft, ETriggerEvent::Completed, this, &UPlayerCamera::EndLean);
	PlayerInput->BindAction(ia_LeanRight, ETriggerEvent::Started, this, &UPlayerCamera::BeginLeanRight);
	PlayerInput->BindAction(ia_LeanRight, ETriggerEvent::Completed, this, &UPlayerCamera::EndLean);
}

void UPlayerCamera::LookAround(const FInputActionValue& inputValue)
{
	if (me->bUseControllerRotationYaw)
	{
		me->bUseControllerRotationYaw = false; // bUseControllerRotationYaw�� ���༭ �ֺ� �þ߸� �ѷ� �� �� �ְ� �Ѵ�.
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
	if (me->bIsTPS == true) // ���� 3��Ī ������ �� 1��Ī�� �ٲ��ش�
	{
		me->bIsTPS = false;
		me->tpsCamComp->SetActive(false);
		me->fpsCamComp->SetActive(true);
		me->GetMesh()->SetOwnerNoSee(true); // 1��Ī�� �� �޽� �� ���̵���
	}
	else // ���� 1��Ī ������ ��
	{
		me->bIsTPS = true;
		me->tpsCamComp->SetActive(true);
		me->fpsCamComp->SetActive(false);
		me->GetMesh()->SetOwnerNoSee(false);
	}
}

void UPlayerCamera::BeginLeanLeft()
{
	me->TargetLeanAngle = -15.0f; // �������� 15�� ����
}

void UPlayerCamera::BeginLeanRight()
{
	me->TargetLeanAngle = 15.0f; // �������� 15�� ����
}

void UPlayerCamera::EndLean()
{
	me->TargetLeanAngle = 0.0f; // ���� �ʱ�ȭ
}