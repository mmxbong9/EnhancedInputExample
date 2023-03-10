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
#include "Blueprint/UserWidget.h"


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
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("TODO: ???????????? ?????? ?????? ????????????."));

	if (PlayerInfoWidget == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerInfoWidget ????????? ???????????? ????????????."));
		return;
	}
	
	if (PlayerInfoWidgetInstance == nullptr)
	{
		PlayerInfoWidgetInstance = CreateWidget(GetWorld(), PlayerInfoWidget);
		PlayerInfoWidgetInstance->AddToViewport();
	}
	else
	{
		if (PlayerInfoWidgetInstance->IsInViewport())
		{
			PlayerInfoWidgetInstance->RemoveFromParent();
			PlayerInfoWidgetInstance = nullptr;
		}
	}
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

// Menu: ???????????? ?????? ??? UI ?????? Action.
void ATPPlayerController::SetupMenuBinding()
{
	UE_LOG(LogClass, Display, TEXT("SetupMenuBinding()"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Menu??? Input ????????????."));

	// ?????? ?????? ?????? ??? Menu ??????.
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

// Play: ????????? ??????, ?????? ??? ????????? ?????? Action.
void ATPPlayerController::SetupPlayBinding()
{
	UE_LOG(LogClass, Display, TEXT("SetupPlayBinding()"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Play??? Input ????????????."));
	
	// ?????? ?????? ?????? ??? Play ??????.
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
