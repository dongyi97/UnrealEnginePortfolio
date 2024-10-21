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

	// 마우스 상하
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* ia_LookUp;
	void LookUp(const struct FInputActionValue& inputValue);

	// 마우스 좌우
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* ia_Turn;
	void Turn(const struct FInputActionValue& inputValue);

public:

	// 이동
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* ia_Move;
	void Move(const struct FInputActionValue& inputValue);

	// 걷기 속도
	UPROPERTY(EditAnywhere, Category = PlayerSetting)
	float walkSpeed = 200;
	// 뛰기 속도
	UPROPERTY(EditAnywhere, Category = PlayerSetting)
	float runSpeed = 600;

	// 달리기
	UPROPERTY(EditDefaultsOnly, category = "Input")
	class UInputAction* ia_PlayerRun;
	void Run();
	bool bIsRunning; // 달리기 여부

	// 점프
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* ia_PlayerJump;
	void InputJump(const struct FInputActionValue& inputValue);
	/*
	//웅크리기
	UPROPERTY(EditDefaultsOnly, category = "Input")
	class UInputAction* ia_Crouch;
	void PlayerCrouch();
	bool bIsCrouched; // 웅크리기 여부

	// 엎드리기
	UPROPERTY(EditDefaultsOnly, category = "Input")
	class UInputAction* ia_Prone;
	void Prone();
	bool bIsProne; // 엎드리기 여부
	float ProneWalkSpeed; // 엎드리기 시 이동 속도
	float PronedCapsuleHalfHeight; // 엎드리기 시 캡슐 높이

	float StandingCapsuleHalfHeight; // 평소 캡슐 높이
	*/
};
