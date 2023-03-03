// Fill out your copyright notice in the Description page of Project Settings.


#include "GeometryPlayerController.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GeometryPawn.h"


DEFINE_LOG_CATEGORY_STATIC(LogGeometryPlayerController, All, All)

void AGeometryPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("ChangePawn", IE_Pressed, this, &AGeometryPlayerController::ChangePawn);
}

void AGeometryPlayerController::ChangePawn()
{
	if (Pawns.Num() <= 1)
	{
		return;
	}

	AGeometryPawn* CurrentPawn = Cast<AGeometryPawn>(Pawns[CurrentPawnIndex]);
	CurrentPawnIndex = (CurrentPawnIndex + 1) % Pawns.Num();
	
	if (!CurrentPawn) { return; }

	UE_LOG(LogGeometryPlayerController, Error, TEXT("Change player pawn"));
	Possess(CurrentPawn);
}

void AGeometryPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGeometryPawn::StaticClass(), Pawns);
}