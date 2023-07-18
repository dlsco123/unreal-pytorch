//#include "A_Object.h"

#include "AC_Gen.h"

// Sets default values for this component's properties
UAC_Gen::UAC_Gen()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
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
				Add(obj);
			}
		}
	}
	
}


// Called every frame
void UAC_Gen::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

AA_Object* UAC_Gen::GenObject(int idx, FVector pose)
{
	if (objPool.Num() < 1)

	{
		return nullptr;

	}
	AA_Object* obj = objPool.Pop();

	//위치로 이동

	SetActive(obj, true);
	return obj;
}

AA_Object* UAC_Gen::Create()
{
	FActorSpawnParameters Param;
	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	auto obj = GetWorld()->SpawnActor<AA_Object>(objectFactory, FVector::ZeroVector, FRotator::ZeroRotator, Param);

	if (obj)
	{
		Add(obj);
	}

	return nullptr;
}

void UAC_Gen::Add(AA_Object* obj)
{
	objPool.AddUnique(Cast<AA_Object>(obj));

	SetActive(obj, false);
}

void UAC_Gen::SetActive(AA_Object* obj, bool isActive)
{
	obj->SetActorHiddenInGame(!isActive);
	obj->SetActorEnableCollision(isActive);
	obj->SetActorTickEnabled(isActive);
}
