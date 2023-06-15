// Copyright Epic Games, Inc. All Rights Reserved.

#include "HamburgerHellGameMode.h"
#include "HamburgerHellHUD.h"
#include "HamburgerHellCharacter.h"
#include "UObject/ConstructorHelpers.h"

AHamburgerHellGameMode::AHamburgerHellGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AHamburgerHellHUD::StaticClass();
}
