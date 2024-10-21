// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyCharacter.h"
#include <GameFramework/CharacterMovementComponent.h>
#include "PlayerBaseComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UPlayerBaseComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerBaseComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// ����� �Է� ���� ó�� �Լ�
	virtual void SetupInputBinding(class UEnhancedInputComponent* PlayerInput) {};

	// �ش� ������Ʈ�� ������ ����
	UPROPERTY()
	AMyCharacter* me;

	UPROPERTY()
	UCharacterMovementComponent* moveComp;

		
};
