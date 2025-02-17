// Copyright 2022-2023 Ivan Baktenkov. All Rights Reserved.

#include "TargetManager.h"
#include "Engine/World.h"

UTargetManager::UTargetManager()
{
	//Do something.
}

UTargetManager& UTargetManager::Get(UWorld& InWorld)
{
	checkf(InWorld.HasSubsystem<ThisClass>(), TEXT("Unable to access the TargetManager subsystem."));
	return *InWorld.GetSubsystem<ThisClass>();
}

void UTargetManager::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	Targets.Reserve(20);
}

bool UTargetManager::DoesSupportWorldType(const EWorldType::Type Type) const
{
	return Type == EWorldType::Game || Type == EWorldType::PIE;
}

bool UTargetManager::RegisterTarget(UTargetComponent* Target)
{
	bool bHasAlreadyBeen = true;

	if (Target)
	{
		Targets.Add(Target, &bHasAlreadyBeen);
	}

	return !bHasAlreadyBeen;
}

bool UTargetManager::UnregisterTarget(UTargetComponent* Target)
{
	return Targets.Remove(Target) > 0;
}
