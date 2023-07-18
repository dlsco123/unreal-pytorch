// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "A_Object.generated.h"

UCLASS()
class ONNX_API AA_Object : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AA_Object();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = "Collision")
		class USphereComponent* collision;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMeshComponent* meshComp;
	UPROPERTY(VisibleAnywhere)
		int idx;
};
