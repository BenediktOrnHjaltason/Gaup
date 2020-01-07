// Fill out your copyright notice in the Description page of Project Settings.


#include "Gaupa.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AGaupa::AGaupa()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void AGaupa::BeginPlay()
{
	Super::BeginPlay();
	SkeletalMeshGaup = GetMesh();
	OurMoveComp = GetCharacterMovement();
}

// Called every frame
void AGaupa::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ForwardBackwardAxisValue == 0 && SidewaysAxisValue == 0) return;
	GetMesh()->SetRelativeRotation(FRotator(0, UKismetMathLibrary::DegAtan2(SidewaysAxisValue,ForwardBackwardAxisValue)+90, 0));
}

// Called to bind functionality to input
void AGaupa::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("ForwardBackward", this, &AGaupa::MoveForwardBackward);
	PlayerInputComponent->BindAxis("RightLeft", this, &AGaupa::MoveRightLeft);
	PlayerInputComponent->BindAxis("GaupeYaw", this, &AGaupa::GaupeYaw);
	PlayerInputComponent->BindAxis("SpringArmPitch", this, &AGaupa::SpringArmPitch);
	PlayerInputComponent->BindAction("ShortenSpringArm", IE_Pressed, this, &AGaupa::ShortenSpringArm);
	PlayerInputComponent->BindAction("LengthenSpringArm", IE_Pressed, this, &AGaupa::LengthenSpringArm);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AGaupa::StartRunning);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AGaupa::StopRunning);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AGaupa::Jump);

}

void AGaupa::MoveForwardBackward(float AxisValue)
{
	ForwardBackwardAxisValue = AxisValue;
	AddMovementInput(GetActorForwardVector(), AxisValue);
}

void AGaupa::MoveRightLeft(float AxisValue)
{
	SidewaysAxisValue = AxisValue;
	AddMovementInput(GetActorRightVector(), AxisValue);
}

void AGaupa::GaupeYaw(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void AGaupa::SpringArmPitch(float AxisValue)
{
	SpringArm->SetRelativeRotation(SpringArm->GetRelativeRotation() + FRotator(AxisValue, 0, 0));
}

void AGaupa::LengthenSpringArm()
{
	if ((SpringArm->TargetArmLength + 30) < 701)
		SpringArm->TargetArmLength += 30;
}

void AGaupa::ShortenSpringArm()
{
	if ((SpringArm->TargetArmLength - 30) > 129)
		SpringArm->TargetArmLength -= 30;
}

void AGaupa::StartRunning()
{
	OurMoveComp->MaxWalkSpeed = RunSpeed;
}
void AGaupa::StopRunning()
{
	OurMoveComp->MaxWalkSpeed = WalkSpeed;
}

void AGaupa::Jump()
{
	UE_LOG(LogTemp, Warning, TEXT("Jump pressed"))
	RunJumpAnim();
	ACharacter::Jump();
}