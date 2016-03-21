// Fill out your copyright notice in the Description page of Project Settings.

#include "StudyProject.h"
#include "StudyCharacter.h"
#include "FPSProjectile.h"


// Sets default values
AStudyCharacter::AStudyCharacter()
{
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->AttachParent = GetCapsuleComponent();
	FirstPersonCameraComponent->RelativeLocation = FVector(0.f, 0.f, 50.f + BaseEyeHeight);
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	FirstPersonMesh->SetOnlyOwnerSee(true);
	FirstPersonMesh->AttachParent = FirstPersonCameraComponent;
	FirstPersonMesh->bCastDynamicShadow = false;
	FirstPersonMesh->CastShadow = false;

	GetMesh()->SetOwnerNoSee(true);
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

	InputComponent->BindAction("Fire", IE_Pressed, this, &AStudyCharacter::OnFire);
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

void AStudyCharacter::OnFire()
{
	if (ProjectileClass != nullptr)
	{
		FVector CameraLoc;
		FRotator CameraRot;

		GetActorEyesViewPoint(CameraLoc, CameraRot);

		const FVector MuzzleLocation = CameraLoc + FTransform(CameraRot).TransformVector(MuzzleOffset);
		FRotator MuzzleRotation = CameraRot;
		MuzzleRotation.Pitch += 10.f;

		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;

			AFPSProjectile* const Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass
																				, MuzzleLocation
																				, MuzzleRotation
																				, SpawnParams);
			if (Projectile != nullptr)
			{
				const FVector LaunchDir = MuzzleRotation.Vector();
				Projectile->InitVelocity(LaunchDir);
			}
		}
	}
}

