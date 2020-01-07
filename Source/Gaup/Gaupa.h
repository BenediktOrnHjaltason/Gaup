// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Gaupa.generated.h"

UCLASS()
class GAUP_API AGaupa : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGaupa();

	UPROPERTY(EditAnywhere)
		USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere)
		UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float WalkSpeed;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float RunSpeed;




	void MoveForwardBackward(float AxisValue);
	void MoveRightLeft(float AxisValue);
	void GaupeYaw(float AxisValue);
	void SpringArmPitch(float AxisValue);
	void LengthenSpringArm();
	void ShortenSpringArm();
	void StartRunning();
	void StopRunning();
	void Jump();

	UFUNCTION(BlueprintImplementableEvent)
		void RunJumpAnim();

	//MeshRotation

	float ForwardBackwardAxisValue;
	float SidewaysAxisValue;

	USkeletalMeshComponent* SkeletalMeshGaup;
	UCharacterMovementComponent* OurMoveComp;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
