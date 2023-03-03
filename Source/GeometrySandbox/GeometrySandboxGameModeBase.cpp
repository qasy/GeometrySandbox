// Copyright Epic Games, Inc. All Rights Reserved.


#include "GeometrySandboxGameModeBase.h"
#include "GeometryPawn.h"
#include "GeometryPlayerController.h"

AGeometrySandboxGameModeBase::AGeometrySandboxGameModeBase()
{
	DefaultPawnClass = AGeometryPawn::StaticClass();
	PlayerControllerClass = AGeometryPlayerController::StaticClass();

}