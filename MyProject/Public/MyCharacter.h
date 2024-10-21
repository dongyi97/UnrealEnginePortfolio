// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseWeapon.h"
//#include "WeaponBase.h"
#include "MyCharacter.generated.h"


UCLASS()
class MYPROJECT_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class USpringArmComponent* springArmComp;
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent* tpsCamComp; // 3인칭 카메라
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent* fpsCamComp; // 1인칭 카메라

public:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext* imc_MyProject;

	// 오브젝트와 상호작용
	UPROPERTY(EditDefaultsOnly, category = "Input")
	class UInputAction* ia_Interact;
	void Interact();

	// 상호작용 범위
	UPROPERTY(EditDefaultsOnly, Category = DetectionDistance)
	int LineTraceDetectionDistance = 2000;
	
	// 카메라 인칭 여부
	bool bIsTPS;

	// 이동 처리
	void Move();
	FVector direction;
	
	// 기울기 상태 함수
	void Lean(float DeltaTime);
	float CurrentLeanAngle; // 현재 기울기 각도
	float TargetLeanAngle; // 목표 기울기 각도
	float LeanInterpSpeed; // 기울기 속도

	// 총 스켈레탈 메시
	//UPROPERTY(VisibleAnywhere, Category=GunMesh)
	//class USkeletalMeshComponent* gunMeshComp;

	// 총구
	//UPROPERTY(EditDefaultsOnly, Category=Muzzle)
	//TSubclassOf<class ABullet> muzzle;

	// 2개의 무기 슬롯
	class AWeaponBase* WeaponSlots[2] = { nullptr, nullptr };
	// 현재 장착 중인 무기 슬롯 인덱스 (0 또는 1)
	int32 CurrentWeaponSlot = 0; 

	// 자동차 탑승 여부
	bool inCar = false;

	// 크로스 헤어 
	UPROPERTY(EditDefaultsOnly, Category = CrosshairUI)
	TSubclassOf<class UUserWidget> crosshairUIFactory;
	UPROPERTY()
	class UUserWidget* crosshairUI;

public:
	UPROPERTY(VisibleAnywhere, Category = Component)
	class UPlayerBaseComponent* playerMove;
	UPROPERTY(VisibleAnywhere, Category = Component)
	class UPlayerBaseComponent* playerWeapon;
	UPROPERTY(VisibleAnywhere, Category = Component)
	class UPlayerBaseComponent* playerCamera;

	// 현재 HP
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = HP)
	int32 HP;
	// 최초 HP
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = HP)
	int32 initialHP = 10;

	// 피격시 함수
	UFUNCTION(BlueprintCallable, Category = HP)
	void OnHitEvent();

	// 게임오버 함수
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Health)
	void OnGameOver();

	// 총 킬 수
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Kill)
	int32 TotalKill = 0;

	// 승리종료 함수
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Health)
	void YouWin();

	// 현재 무기 탄약 수
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Ammo)
	int32 CurrentWeaponAmmo = 0;
};
