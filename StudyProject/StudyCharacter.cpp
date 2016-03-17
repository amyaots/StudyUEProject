// Fill out your copyright notice in the Description page of Project Settings.

#include "StudyProject.h"
#include "StudyCharacter.h"


// Sets default values
AStudyCharacter::AStudyCharacter()
{
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->AttachParent = CapsuleComponent;
	FirstPersonCameraComponent->RelativeLocation = FVector(0.f, 0.f, 50.f + BaseEyeHeight);
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStudyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("We are using FPSCharacter!"));
	}
}

// Called every frame
void AStudyCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AStudyCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis("MoveForward", this, &AStudyCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AStudyCharacter::MoveRight);
	
	InputComponent->BindAxis("Turn", this, &AStudyCharacter::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, &AStudyCharacter::AddControllerPitchInput);
	
	InputComponent->BindAction("Jump", IE_Pressed, this, &AStudyCharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &AStudyCharacter::StopJumping);
}

void AStudyCharacter::MoveForward(float Val)
{
	if (Controller != nullptr)
	{
		FRotator Rotation = Controller->GetControlRotation();

		if (GetCharacterMovement()->IsMovingOnGround() || GetCharacterMovement()->IsFalling())
		{
			Rotation.Pitch = 0.f;
		}

		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, Val);
	}
}

void AStudyCharacter::MoveRight(float Val)
{
	if (Controller != nullptr)
	{
		FRotator Rotation = Controller->GetControlRotation();

		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		AddMovementInput(Direction, Val);
	}
}

