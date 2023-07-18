// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
// NNI Plugin
#include "NeuralNetwork.h"

//#include "FileMediaSource.h"

#include "MyNeuralNetwork.generated.h"


UCLASS()
class ONNX_API UMyNeuralNetwork : public UNeuralNetwork
{
	GENERATED_BODY()

public:
	UPROPERTY(Transient)
		UNeuralNetwork* Network = nullptr;

	UMyNeuralNetwork();


	void URunModel(TArray<float>& image, TArray<float>& results);
	FVector FindCenter(float x1, float y1, float x2, float y2);

};
