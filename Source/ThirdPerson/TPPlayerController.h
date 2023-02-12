// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "TPPlayerController.generated.h"


UCLASS()
class THIRDPERSON_API ATPPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATPPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	void Jump    (const struct FInputActionValue& Value);
	void StopJump(const struct FInputActionValue& Value);
	void Move    (const struct FInputActionValue& Value);
	void Look    (const struct FInputActionValue& Value);

protected:
	virtual void BeginPlay() override;
	virtual void Tick	  (float DeltaTime) override;
	virtual void EndPlay  (const EEndPlayReason::Type EndPlayReason) override;

	virtual void SetupInputComponent() override;

private:
	void SetupMenuBinding();
	void SetupPlayBinding();

	bool bIsPlayMode = false;
	
	// 플레이어 상태에 따른 인풋 모드 toggle.
	void ToggleInputMode    (const FInputActionValue& Value);
	void ShowPopupPlayerInfo(const FInputActionValue& Value);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Enhanced Input")
	class UInputMappingContext* InputPlayMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Enhanced Input")
	class UInputMappingContext* InputMenuMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Enhanced Input")
	class UTPInputMenuData* InputMenuActions;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Enhanced Input")
	class UTPInputPlayData* InputPlayActions;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Camera Shake")
	TSubclassOf<UCameraShakeBase> CameraShake;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="User Widget")
	TSubclassOf<UUserWidget> PlayerInfoWidget;
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="User Widget")
	UUserWidget* PlayerInfoWidgetInstance;
};
