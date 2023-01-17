// Fill out your copyright notice in the Description page of Project Settings.


#include "GeometryHubActor.h"
#include "Engine/World.h"

DEFINE_LOG_CATEGORY_STATIC(LogGeometryHub, All, All)

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
	//DoActorSpawn1();
	//DoActorSpawn2();
	DoActorSpawn3();	

		
}

// Called every frame
void AGeometryHubActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGeometryHubActor::DoActorSpawn1()
{
	UWorld* World = GetWorld();
	if (World)
	{
		World->SpawnActor(GeometryClass);

		// SPAWN TYPE 1: Me, try to spawn N object with SpawnActor()
		for (int32 i = 0; i < 5; ++i)
		{
			const FTransform Transform = FTransform(FRotator::ZeroRotator, FVector(0.0f, 200.0f + 200.0f * i, 0.0f));
			ABaseGeometryActor* BaseGeometryActor = World->SpawnActor<ABaseGeometryActor>(GeometryClass, Transform);

			if (BaseGeometryActor)
			{
				FGeometryData Data;
				Data.MoveType = (FMath::RandBool()) ? EMovementType::Sin : EMovementType::Static;
				BaseGeometryActor->SetGeometryData(Data);
			}
		}
	}
}

void AGeometryHubActor::DoActorSpawn2()
{
	UWorld* World = GetWorld();
	if (World)
	{
		// SPAWN TYPE 2: Me, try to spawn N object with SpawnActorDeffered
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

		for (const FGeometryPayload &Payload : GeometryPayloads)
		{
			ABaseGeometryActor* BaseGeometryActor = World->SpawnActorDeferred<ABaseGeometryActor>(Payload.GeometryClass, Payload.InitialTransform);

			if (BaseGeometryActor)
			{
				BaseGeometryActor->SetGeometryData(Payload.Data);
				BaseGeometryActor->FinishSpawning(Payload.InitialTransform);
			}

		}
	}	
}

void AGeometryHubActor::DoActorSpawn3()
{
	UWorld* World = GetWorld();
	if (World)
	{
		// SPAWN TYPE 3: Me, try to spawn N object with SpawnActorDeffered and range version of "for"
		for (const FGeometryPayload& Payload : GeometryPayloads)
		{
			ABaseGeometryActor* BaseGeometryActor = World->SpawnActorDeferred<ABaseGeometryActor>(Payload.GeometryClass, Payload.InitialTransform);
			if (BaseGeometryActor)
			{
				BaseGeometryActor->SetGeometryData(Payload.Data);
				BaseGeometryActor->OnColorChanged.AddDynamic(this, &AGeometryHubActor::OnColorChanged);
				BaseGeometryActor->OnTimerFinished.AddUObject(this, &AGeometryHubActor::OnTimerFinished);
				BaseGeometryActor->FinishSpawning(Payload.InitialTransform);
			}
		}
	}
}

void AGeometryHubActor::OnColorChanged(const FLinearColor& Color, const FString& Name)
{
	UE_LOG(LogGeometryHub, Warning, TEXT("Actor name: %s Color: %s"), *Name, *Color.ToString());
}

void AGeometryHubActor::OnTimerFinished(AActor* Actor)
{
	if (!Actor) { return; }
	
	UE_LOG(LogGeometryHub, Error, TEXT("Timer finished: %s"), *Actor->GetName());

	ABaseGeometryActor* Geometry = Cast<ABaseGeometryActor>(Actor);
	if (!Geometry) { return; }

	UE_LOG(LogGeometryHub, Display, TEXT("Cast is success, amplitude %f"), Geometry->GetGeometryData().Amplitude);
	Geometry->Destroy();	
}

