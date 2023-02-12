// Fill out your copyright notice in the Description page of Project Settings.

#include "TPPlayerController.h"

#include "TPCharacter.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TPInputPlayData.h"
#include "TPInputMenuData.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"


ATPPlayerController::ATPPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void ATPPlayerController::Jump(const FInputActionValue& Value)
{
	UE_LOG(LogClass, Display, TEXT("Jump()"));
	
	if(GetCharacter() == nullptr)
	{
		return;
	}

	GetCharacter()->Jump();
}

void ATPPlayerController::StopJump(const struct FInputActionValue& Value)
{
	UE_LOG(LogClass, Display, TEXT("StopJump()"));

	if(GetCharacter() == nullptr)
	{
		return;
	}

	GetCharacter()->StopJumping();
}

void ATPPlayerController::Move(const FInputActionValue& Value)
{
	//UE_LOG(LogClass, Display, TEXT("Move Vector: %s"), *Value.Get<FVector2d>().ToString());

	ATPCharacter* TPCharacter = Cast<ATPCharacter>(GetCharacter());

	if(TPCharacter == nullptr)
	{
		return;
	}
	
	TPCharacter->Move(Value.Get<FVector2d>());
}

void ATPPlayerController::Look(const FInputActionValue& Value)
{
	//UE_LOG(LogClass, Display, TEXT("LootAt Axis Vector: %s"), *Value.Get<FVector2d>().ToString());

	ATPCharacter* TPCharacter = Cast<ATPCharacter>(GetCharacter());

	if(TPCharacter == nullptr)
	{
		return;
	}
	
	TPCharacter->Look(Value.Get<FVector2d>());
}

void ATPPlayerController::ToggleInputMode(const FInputActionValue& Value)
{
	if(bIsPlayMode)
	{
		SetupMenuBinding();
	}
	else
	{
		SetupPlayBinding();
	}

	UE_LOG(LogClass, Display, TEXT("Now PlayMode=%s"), bIsPlayMode ? TEXT("TRUE") : TEXT("FALSE"));
}

void ATPPlayerController::ShowPopupPlayerInfo(const FInputActionValue& Value)
{
	UE_LOG(LogClass, Display, TEXT("ShowPopupPlayerInfo()"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("TODO: 플레이어 정보 위젯 띄워야함."));
}

void ATPPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ATPPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATPPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ATPPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	SetupPlayBinding();
}

// Menu: 플레이어 시선 및 UI 관련 Action.
void ATPPlayerController::SetupMenuBinding()
{
	UE_LOG(LogClass, Display, TEXT("SetupMenuBinding()"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Menu용 Input 바인딩됨."));

	// 기존 매핑 제거 후 Menu 매핑.
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	Subsystem->ClearAllMappings();
	Subsystem->RemoveMappingContext(InputPlayMapping);
	Subsystem->AddMappingContext(InputMenuMapping, 0);
	
	UEnhancedInputComponent* EIComp = Cast<UEnhancedInputComponent>(InputComponent);
	EIComp->ClearActionBindings();
	EIComp->BindAction(InputMenuActions->InputChangeMode, 	   ETriggerEvent::Triggered, this, &ATPPlayerController::ToggleInputMode);
	EIComp->BindAction(InputMenuActions->InputLook, 	  	   ETriggerEvent::Triggered, this, &ATPPlayerController::Look);
	EIComp->BindAction(InputMenuActions->ToggleShowPlayerInfo, ETriggerEvent::Triggered, this, &ATPPlayerController::ShowPopupPlayerInfo);
	
	bIsPlayMode = false;
}

// Play: 캐릭터 이동, 시선 등 캐릭터 관련 Action.
void ATPPlayerController::SetupPlayBinding()
{
	UE_LOG(LogClass, Display, TEXT("SetupPlayBinding()"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Play용 Input 바인딩됨."));
	
	// 기존 매핑 제거 후 Play 매핑.
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	Subsystem->ClearAllMappings();
	Subsystem->RemoveMappingContext(InputMenuMapping);
	Subsystem->AddMappingContext(InputPlayMapping, 0);
	
	UEnhancedInputComponent* EIComp = Cast<UEnhancedInputComponent>(InputComponent);
	EIComp->ClearActionBindings();
	EIComp->BindAction(InputPlayActions->InputChangeMode, ETriggerEvent::Triggered, this, &ATPPlayerController::ToggleInputMode);
	EIComp->BindAction(InputPlayActions->InputJump, 	  ETriggerEvent::Triggered, this, &ATPPlayerController::Jump);
	EIComp->BindAction(InputPlayActions->InputJump, 	  ETriggerEvent::Completed, this, &ATPPlayerController::StopJump);
	EIComp->BindAction(InputPlayActions->InputMove, 	  ETriggerEvent::Triggered, this, &ATPPlayerController::Move);
	EIComp->BindAction(InputPlayActions->InputLook, 	  ETriggerEvent::Triggered, this, &ATPPlayerController::Look);
	
	bIsPlayMode = true;
}
