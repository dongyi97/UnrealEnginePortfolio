// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerBaseComponent.h"
#include "PlayerCamera.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UPlayerCamera : public UPlayerBaseComponent
{
	GENERATED_BODY()
	
public:
	UPlayerCamera();

	virtual void SetupInputBinding(class UEnhancedInputComponent* PlayerInput) override;

	// 주변 보기
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* ia_LookAround;
	void LookAround(const struct FInputActionValue& inputValue);

	// 시점 바꾸기
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* ia_CameraSwitch;
	void CameraSwitch(const struct FInputActionValue& inputValue);
	
	// 기울이기
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* ia_LeanLeft;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* ia_LeanRight;

	void BeginLeanLeft();
	void BeginLeanRight();
	void EndLean();
	
};
