// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerDetectionComponent.h"
#include <Components/SphereComponent.h> // USphereComponent
#include <MyCharacter.h>
#include <Kismet/GameplayStatics.h>
#include "TimerManager.h" // TimerManager ���� ���
#include "Components/PrimitiveComponent.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include "Blueprint/UserWidget.h"
#include "MyProject/MyProject.h"
#include "DrawDebugHelpers.h"
#include "BaseInteractive.h"

// Sets default values for this component's properties
UPlayerDetectionComponent::UPlayerDetectionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerDetectionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	// ������Ʈ�� ������ ������ ���� ������Ʈ ��������
	if (AActor* Owner = GetOwner())
	{
		UE_LOG(TPS, Warning, TEXT("Owner founded"))
		// ������ ���� ������Ʈ�� ��������
		USphereComponent* DetectionSphere = Owner->FindComponentByClass<USphereComponent>();
		//DetectionSphere->getradius
		if (DetectionSphere)
		{
			UE_LOG(TPS, Warning, TEXT("DetectionSphere founded"))
			// �浹 �̺�Ʈ ���ε�
			DetectionSphere->OnComponentBeginOverlap.AddDynamic(this, &UPlayerDetectionComponent::OnOverlapBegin);
			DetectionSphere->OnComponentEndOverlap.AddDynamic(this, &UPlayerDetectionComponent::OnOverlapEnd);
		}
	}
	
}


// Called every frame
void UPlayerDetectionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlayerDetectionComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(TPS, Warning, TEXT("OnOverlapBegin"))
	if (AMyCharacter* Player = Cast<AMyCharacter>(OtherActor))
	{			
		// ���� �Լ� ȣ���� ���� Ÿ�̸� ����
		Player->GetWorldTimerManager().SetTimer(DetectionTimerHandle, this, &UPlayerDetectionComponent::CheckIfInView, 0.1f, true);
		// GetWorldTimerManager().SetTimer(DetectionTimerHandle, this, &UPlayerDetectionComponent::CheckIfInView, 0.1f, true);
	}
}

void UPlayerDetectionComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(TPS, Warning, TEXT("OnOverlapEnd"))
	if (AMyCharacter* Player = Cast<AMyCharacter>(OtherActor))
	{
		// Ÿ�̸� ����
		Player->GetWorldTimerManager().ClearTimer(DetectionTimerHandle);
		HideInteractionUI();  // ������ ����� UI ����
		//GetWorldTimerManager().ClearTimer(DetectionTimerHandle);
	}
}

void UPlayerDetectionComponent::CheckIfInView()
{
	AMyCharacter* Player = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!Player) return;
	/*
	FVector PlayerViewLocation;
	FRotator PlayerViewRotation;
	Player->GetController()->GetPlayerViewPoint(PlayerViewLocation, PlayerViewRotation);

	FVector DirectionToObject = (GetActorLocation() - PlayerViewLocation).GetSafeNormal();
	float DotProduct = FVector::DotProduct(PlayerViewRotation.Vector(), DirectionToObject);

	// �þ� ������ �Ǵ��� UI ǥ��
	float ViewAngle = 30.0f;
	if (DotProduct > FMath::Cos(FMath::DegreesToRadians(ViewAngle)))
	{
		ShowInteractionUI();
	}
	else
	{
		HideInteractionUI();
	}
	*/
	//////////////////////////////////////////////////////////////////////////////////
	FHitResult HitResult;
	FVector Start = Player->tpsCamComp->GetComponentLocation();
	FVector End = Start + (Player->tpsCamComp->GetForwardVector() * Player->LineTraceDetectionDistance);
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Player);
	//UE_LOG(TPS, Warning, TEXT("Interact: Key pushed"))
	// �ü��� �ִ� ������Ʈ ����
	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params))
	{
		AActor* HitActor = HitResult.GetActor();
		if (HitActor && HitActor->GetClass()->ImplementsInterface(UBaseInteractive::StaticClass()))
		{
			//UE_LOG(TPS, Warning, TEXT("ui make"))
			//IBaseInteractive::Execute_Interact(HitActor, this);
			ShowInteractionUI();
		}
		//ShowInteractionUI();
		else
		{
			HideInteractionUI();
		}
		//UE_LOG(TPS, Warning, TEXT("what is this"))
		//HideInteractionUI();
	}
	else
	{
		HideInteractionUI();
		//UE_LOG(TPS, Warning, TEXT("ui hide"))
	}
	//DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 5.0f, 0, 2.0f);
}

void UPlayerDetectionComponent::ShowInteractionUI()
{
	if (!InteractionWidget && InteractionWidgetClass)  // ������ ����, Ŭ������ ��ȿ�� ���� ����
	{
		InteractionWidget = CreateWidget<UUserWidget>(GetWorld(), InteractionWidgetClass);
		if (InteractionWidget)
		{
			InteractionWidget->AddToViewport();
		}
	}
	else if (InteractionWidget)
	{
		InteractionWidget->SetVisibility(ESlateVisibility::Visible);  // ������ �̹� �����ϸ� ǥ�� ���·� ��ȯ
	}
}

void UPlayerDetectionComponent::HideInteractionUI()
{
	if (InteractionWidget)
	{
		InteractionWidget->SetVisibility(ESlateVisibility::Hidden);  // ������ �����
	}
}

