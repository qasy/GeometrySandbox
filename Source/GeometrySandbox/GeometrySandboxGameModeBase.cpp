// Copyright Epic Games, Inc. All Rights Reserved.


#include "GeometrySandboxGameModeBase.h"
#include "GeometryPawn.h"

AGeometrySandboxGameModeBase::AGeometrySandboxGameModeBase()
{
	DefaultPawnClass = AGeometryPawn::StaticClass();
}