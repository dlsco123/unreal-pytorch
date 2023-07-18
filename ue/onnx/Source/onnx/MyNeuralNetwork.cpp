// Fill out your copyright notice in the Description page of Project Settings.





#include "MyNeuralNetwork.h"


UMyNeuralNetwork::UMyNeuralNetwork()
{
	Network = nullptr;
}

FVector UMyNeuralNetwork::FindCenter(float x1, float y1, float x2, float y2)
{
	FVector center = FVector(0,0,0);
	float z = 50;

	center = FVector((x2 + x1) / 2, (y1 + y2) / 2, z);

	return center;
}

void UMyNeuralNetwork::URunModel(TArray<float>& image, TArray<float>& results)
{
	if (Network == nullptr || !Network->IsLoaded()) {
		return;
	}

	// Running inference
	Network->SetInputFromArrayCopy(image);

	// Run UNeuralNetwork
	Network->Run();

	// Read and print OutputTensor
	TArray<float> OutputTensor = Network->GetOutputTensor().GetArrayCopy<float>();

	// Create array of the correct pixel values from results
	results.Reset();
	//int channelStride = image.Num() / 3;
	int channelStride = 6;			  // x1, y1, x2, y2, score, label
	int num_Detection = OutputTensor.Num() / channelStride;

	results.Reserve(num_Detection * 3); // X,Y, �������� a 

	for (size_t i = 0; i < num_Detection; i++) {
		if (OutputTensor[i * channelStride + 5] >= 0.85 && OutputTensor[i * channelStride + 5] == 0)
		{
			FVector center = FindCenter(OutputTensor[i* channelStride], OutputTensor[i * channelStride +1], OutputTensor[i * channelStride +2], OutputTensor[i * channelStride +3]);

			results.Add(center.X);							// center X
			results.Add(center.Y);							// center y
		}
	}

	UE_LOG(LogTemp, Log, TEXT("Results created successfully."))
}