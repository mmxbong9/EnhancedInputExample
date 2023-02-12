// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TPCharacter.generated.h"

UCLASS()
class THIRDPERSON_API ATPCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ATPCharacter();

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	// TODO: 현재 controller 에서 호출 하고 있는데, character 내에서 호출할수 있도록 바꾸자.
//protected:
public:
	/** Called for movement input */
	void Move(const FVector2d& InMoveVector);

	/** Called for looking input */
	void Look(const FVector2d& InMoveVector);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent*  GetFollowCamera() const { return FollowCamera; }
};
