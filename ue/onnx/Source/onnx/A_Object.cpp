// Fill out your copyright notice in the Description page of Project Settings.


#include "A_Object.h"

// Sets default values
AA_Object::AA_Object()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AA_Object::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AA_Object::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

