// Fill out your copyright notice in the Description page of Project Settings.

#include "StudyProject.h"
#include "StudyGameMode.h"

AStudyGameMode::AStudyGameMode()
{
	// set default pawn class to our Blueprinted character 
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnObject(TEXT("Pawn'/Game/Blueprint/StudyBPChar.StudyBPChar_C'"));
	if (PlayerPawnObject.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnObject.Class;
	}
}

void AStudyGameMode::StartPlay()
{
	Super::StartPlay();

	StartMatch();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("HELLO WORLD"));
	}
}

