// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseInteractive.h"
#include "PlayerDetectionComponent.h"
#include "HPPack.generated.h"

UCLASS()
class MYPROJECT_API AHPPack : public AActor, public IBaseInteractive
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHPPack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Collision ������Ʈ
	UPROPERTY(VisibleAnywhere, Category = Collision)
	class UBoxComponent* collisionComp;

	// �ܰ� ������Ʈ
	UPROPERTY(VisibleAnywhere, Category = BodyMesh)
	class USkeletalMeshComponent* bodyMeshComp;

	// ������ ���� ������Ʈ
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USphereComponent* DetectionSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UPlayerDetectionComponent* DetectionComponent;

	UFUNCTION(BlueprintCallable, Category = "Recovery")
	virtual void Interact_Implementation(AMyCharacter* Character) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recovery")
	int32 Recovery;
};