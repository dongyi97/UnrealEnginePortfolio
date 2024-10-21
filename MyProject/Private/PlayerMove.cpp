// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMove.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Components/CapsuleComponent.h"

UPlayerMove::UPlayerMove()
{
	// Tick �Լ� ȣ��ǵ��� ó��
	PrimaryComponentTick.bCanEverTick = false;

	// ��ũ���� ��� �ʱ� ����
	//moveComp->NavAgentProps.bCanCrouch = true;
	//bIsCrouched = false;

	// ���帮�� ��� �ʱ� ����
	//bIsProne = false;
	//StandingCapsuleHalfHeight = me->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
	//PronedCapsuleHalfHeight = 20.0f;
}

void UPlayerMove::BeginPlay()
{
	Super::BeginPlay();

	// �ʱ� �ӵ��� �ȱ�� ����
	moveComp->MaxWalkSpeed = walkSpeed;
}

void UPlayerMove::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UPlayerMove::Turn(const FInputActionValue& inputValue)
{
	float value = inputValue.Get<float>();
	me->AddControllerYawInput(value);
}

void UPlayerMove::LookUp(const FInputActionValue& inputValue)
{
	float value = inputValue.Get<float>();
	me->AddControllerPitchInput(value);
}

void UPlayerMove::SetupInputBinding(UEnhancedInputComponent* PlayerInput)
{
	// ī�޶�
	PlayerInput->BindAction(ia_Turn, ETriggerEvent::Triggered, this, &UPlayerMove::Turn);
	PlayerInput->BindAction(ia_LookUp, ETriggerEvent::Triggered, this, &UPlayerMove::LookUp);
	// �̵�
	PlayerInput->BindAction(ia_Move, ETriggerEvent::Triggered, this, &UPlayerMove::Move);
	// �޸���
	PlayerInput->BindAction(ia_PlayerRun, ETriggerEvent::Started, this, &UPlayerMove::Run);
	PlayerInput->BindAction(ia_PlayerRun, ETriggerEvent::Completed, this, &UPlayerMove::Run);
	// ����
	PlayerInput->BindAction(ia_PlayerJump, ETriggerEvent::Started, this, &UPlayerMove::InputJump);
	// ��ũ���� ���ε�
	//PlayerInput->BindAction(ia_Crouch, ETriggerEvent::Started, this, &UPlayerMove::PlayerCrouch);
	//PlayerInput->BindAction(ia_Crouch, ETriggerEvent::Completed, this, &UPlayerMove::PlayerCrouch);
	// ���帮�� ���ε�
	//PlayerInput->BindAction(ia_Prone, ETriggerEvent::Started, this, &UPlayerMove::Prone);
	//PlayerInput->BindAction(ia_Prone, ETriggerEvent::Completed, this, &UPlayerMove::Prone);
}

void UPlayerMove::Move(const FInputActionValue& inputValue)
{
	FVector2D value = inputValue.Get<FVector2D>();

	me->direction.X = value.X;
	me->direction.Y = value.Y;
}

void UPlayerMove::Run()
{
	if (bIsRunning)
	{
		bIsRunning = false;
		me->GetCharacterMovement()->MaxWalkSpeed = walkSpeed;
	}
	else
	{
		bIsRunning = true;
		me->GetCharacterMovement()->MaxWalkSpeed = runSpeed;
	}
}

void UPlayerMove::InputJump(const FInputActionValue& inputValue)
{
	me->Jump();
}
/*
void UPlayerMove::PlayerCrouch()
{
	if (bIsCrouched)
	{
		// ��ũ���� ����
		me->UnCrouch();
		//GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
	}
	else
	{
		// ��ũ���� ����
		me->Crouch();
		//GetCharacterMovement()->MaxWalkSpeed = CrouchWalkSpeed;
	}
}

void UPlayerMove::Prone()
{
	if (bIsProne)
	{
		bIsProne = false;
		//GetCharacterMovement()->bCanJump = true;
		//GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
		me->GetCapsuleComponent()->SetCapsuleHalfHeight(StandingCapsuleHalfHeight);

	}
	else
	{
		bIsProne = true;
		//GetCharacterMovement()->MaxWalkSpeed = ProneWalkSpeed;
		me->GetCapsuleComponent()->SetCapsuleHalfHeight(PronedCapsuleHalfHeight);
	}
}
*/