// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "A_Object.h"

#include "Components/ActorComponent.h"
#include "AC_Gen.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ONNX_API UAC_Gen : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAC_Gen();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AA_Object> objectFactory;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
		TArray<AA_Object*> objPool;

	UPROPERTY(EditAnywhere)
		int objPoolSize = 20;

	AA_Object* GenObject(int idx, FVector pose);
	AA_Object* Create();
	void AddtoPool(AA_Object* obj);
	void SetObjActive(AA_Object* obj, bool isActive);
	AA_Object* SearchObj(int idx);
};
