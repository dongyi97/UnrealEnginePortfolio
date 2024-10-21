// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerBaseComponent.h"
#include "PlayerMove.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UPlayerMove : public UPlayerBaseComponent
{
	GENERATED_BODY()
	
public:

	UPlayerMove();

	virtual void SetupInputBinding(class UEnhancedInputComponent* PlayerInput) override;
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// ���콺 ����
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* ia_LookUp;
	void LookUp(const struct FInputActionValue& inputValue);

	// ���콺 �¿�
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* ia_Turn;
	void Turn(const struct FInputActionValue& inputValue);

public:

	// �̵�
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* ia_Move;
	void Move(const struct FInputActionValue& inputValue);

	// �ȱ� �ӵ�
	UPROPERTY(EditAnywhere, Category = PlayerSetting)
	float walkSpeed = 200;
	// �ٱ� �ӵ�
	UPROPERTY(EditAnywhere, Category = PlayerSetting)
	float runSpeed = 600;

	// �޸���
	UPROPERTY(EditDefaultsOnly, category = "Input")
	class UInputAction* ia_PlayerRun;
	void Run();
	bool bIsRunning; // �޸��� ����

	// ����
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* ia_PlayerJump;
	void InputJump(const struct FInputActionValue& inputValue);
	/*
	//��ũ����
	UPROPERTY(EditDefaultsOnly, category = "Input")
	class UInputAction* ia_Crouch;
	void PlayerCrouch();
	bool bIsCrouched; // ��ũ���� ����

	// ���帮��
	UPROPERTY(EditDefaultsOnly, category = "Input")
	class UInputAction* ia_Prone;
	void Prone();
	bool bIsProne; // ���帮�� ����
	float ProneWalkSpeed; // ���帮�� �� �̵� �ӵ�
	float PronedCapsuleHalfHeight; // ���帮�� �� ĸ�� ����

	float StandingCapsuleHalfHeight; // ��� ĸ�� ����
	*/
};
