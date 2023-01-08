// Fill out your copyright notice in the Description page of Project Settings.


#include "GeometryHubActor.h"
#include "Engine/World.h"

// Sets default values
AGeometryHubActor::AGeometryHubActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGeometryHubActor::BeginPlay()
{
	Super::BeginPlay();
	
	UWorld* World = GetWorld();
	if (World)
	{
		World->SpawnActor(GeometryClass);

		// SPAWN TYPE 1: Me, try to spawn N object with other transform
		for (int32 i = 0; i < 5; ++i)
		{
			const FTransform Transform = FTransform(FRotator::ZeroRotator, FVector(0.0f, 200.0f + 200.0f*i, 0.0f));
			ABaseGeometryActor* BaseGeometryActor = World->SpawnActor<ABaseGeometryActor>(GeometryClass, Transform);

			if (BaseGeometryActor) 
			{
				FGeometryData Data;
				Data.MoveType = (FMath::RandBool()) ? EMovementType::Sin : EMovementType::Static;
				BaseGeometryActor->SetGeometryData(Data);
			}
		}

		// SPAWN TYPE 2: Me, try to spawn N object with other transform 
		for (int32 i = 0; i < 5; ++i)
		{
			const FTransform Transform = FTransform(FRotator::ZeroRotator, FVector(0.0f, 200.0f + 200.0f * i, 500.0f));
			ABaseGeometryActor* BaseGeometryActor = World->SpawnActorDeferred<ABaseGeometryActor>(GeometryClass, Transform);

			if (BaseGeometryActor)
			{
				FGeometryData Data;
				Data.Color = FLinearColor::MakeRandomColor();
				Data.MoveType = (FMath::RandBool()) ? EMovementType::Sin : EMovementType::Static;
				BaseGeometryActor->SetGeometryData(Data);
				BaseGeometryActor->FinishSpawning(Transform);
			}
		}
	}	
}

// Called every frame
void AGeometryHubActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

