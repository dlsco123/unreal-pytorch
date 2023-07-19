#include "AC_Gen.h"

UAC_Gen::UAC_Gen()
{

	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UAC_Gen::BeginPlay()
{
	Super::BeginPlay();

	if (objectFactory)
	{
		for (int i = 0; i < objPoolSize; i++)
		{
			AA_Object* obj = Cast<AA_Object>(Create());
		
			if (obj)
			{
				obj->idx = i;
				AddtoPool(obj);
			}
		}
	}
}

void UAC_Gen::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

AA_Object* UAC_Gen::GenObject(int idx, FVector pose)
{
	if (objPool.Num() < 1)

	{
		return nullptr;

	}
	//AA_Object* obj = objPool.Pop();
	AA_Object* obj = SearchObj(idx);

	if (obj)
	{
		//위치로 이동
		obj->SetActorLocation(pose);

		SetObjActive(obj, true);
	}

	return obj;
}

AA_Object* UAC_Gen::Create()
{
	FActorSpawnParameters Param;
	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	auto obj = GetWorld()->SpawnActor<AA_Object>(objectFactory, FVector::ZeroVector, FRotator::ZeroRotator, Param);

	if (obj)
	{
		AddtoPool(obj);
	}

	return nullptr;
}

void UAC_Gen::AddtoPool(AA_Object* obj)
{
	objPool.AddUnique(Cast<AA_Object>(obj));

	SetObjActive(obj, false);
}

void UAC_Gen::SetObjActive(AA_Object* obj, bool isActive)
{
	obj->SetActorHiddenInGame(!isActive);
	obj->SetActorEnableCollision(isActive);
	obj->SetActorTickEnabled(isActive);
}

AA_Object* UAC_Gen::SearchObj(int idx)
{
	AA_Object* output;
	for (int i = 0; i < objPool.Num(); i++)
	{
		if (objPool[i]->idx == idx)
		{
			output = objPool[i];
			objPool.RemoveAt(i);
			return output;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("%d is already used."), idx);
	return nullptr;
}
