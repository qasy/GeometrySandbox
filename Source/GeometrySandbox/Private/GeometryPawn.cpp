 // Fill out your copyright notice in the Description page of Project Settings.


#include "GeometryPawn.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogGeometryPawn, All, All)

// Sets default values
AGeometryPawn::AGeometryPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	StaticMeshComponent->SetupAttachment(SceneComponent);
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SceneComponent);

}

// Called when the game starts or when spawned
void AGeometryPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGeometryPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!VelocityVector.IsZero())
	{
		const FVector NewLocation = GetActorLocation() + Velocity * DeltaTime * VelocityVector;
		SetActorLocation(NewLocation);
		VelocityVector = FVector::ZeroVector;
	}


}

// Called to bind functionality to input
void AGeometryPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AGeometryPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AGeometryPawn::MoveRight);
}

void AGeometryPawn::MoveForward(float Amount)
{
	UE_LOG(LogGeometryPawn, Display, TEXT("MoveForward: %0.1f"), Amount);
	VelocityVector.X = Amount;
}

void AGeometryPawn::MoveRight(float Amount)
{
	UE_LOG(LogGeometryPawn, Display, TEXT("MoveRight: %0.1f"), Amount);
	VelocityVector.Y = Amount;
}


void AGeometryPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	UE_LOG(LogGeometryPawn, Error, TEXT("%s possessed by %s"), *GetName(), *NewController->GetName());
}

void AGeometryPawn::UnPossessed()
{
	Super::UnPossessed();
	UE_LOG(LogGeometryPawn, Warning, TEXT("%s un possessed"), *GetName());

}
