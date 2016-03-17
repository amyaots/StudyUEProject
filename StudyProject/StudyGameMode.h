// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "StudyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class STUDYPROJECT_API AStudyGameMode : public AGameMode
{
	GENERATED_BODY()

	AStudyGameMode();
	virtual void StartPlay() override;	
	
};
