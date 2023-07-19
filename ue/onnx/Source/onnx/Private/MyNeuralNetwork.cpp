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

int UMyNeuralNetwork::SearchMax(TArray<float> arr)
{
	float max = arr[0];
	int idx = 0;
	for (int i = 0; i < arr.Num()-1; i++)
	{
		if (max < arr[i + 1])
		{
			max = arr[i + 1];
			idx = i + 1;
		}
	}

	return idx;
}

void UMyNeuralNetwork::URunModel(TArray<float>& image, TArray<float>& results)
{
	if (Network == nullptr || !Network->IsLoaded()) 
	{
		UE_LOG(LogTemp, Error, TEXT("Network is null || inst Loaded"));
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
	int channelStride = 85;			  // x1, y1, x2, y2, score, label 80
	int num_Detection = OutputTensor.Num() / channelStride;

	UE_LOG(LogTemp, Warning, TEXT("Output Result size : %d, num_Detection %d"), OutputTensor.Num(), num_Detection);

	results.Reserve(num_Detection * 3); // X,Y, 여유공간 a 

	//UE_LOG(LogTemp, Warning, TEXT("output0 : %f, %f, %f, %f, %f, %f"), OutputTensor[0], OutputTensor[1], OutputTensor[2], OutputTensor[3], OutputTensor[4], int(OutputTensor[5]));

	for (int i = 0; i < num_Detection; i++) {
		//UE_LOG(LogTemp, Warning, TEXT("Label : %d"), OutputTensor[i * channelStride + 5]);
		
		TArray<float> labels;
		// label 부분만 따로 추출 5 ~ 74
		for (int j = 5; j < 85; j++)
		{
			labels.Add(OutputTensor[i * channelStride + j]);
		}
		
		// label 최고값 찾기
		int label = SearchMax(labels);
		//int label = int( OutputTensor[i * channelStride + 5] );
		float coff = OutputTensor[i * channelStride + 5];
		UE_LOG(LogTemp, Warning, TEXT("%d -> label :  %d, coff : %f"), i, label, coff);

		if ( coff >= 0.85 && label == 0)
		{
			// 결과가 두 점 인경우
			//FVector center = FindCenter(OutputTensor[i* channelStride], OutputTensor[i * channelStride +1], OutputTensor[i * channelStride +2], OutputTensor[i * channelStride +3]);

			// 결과가 센터 한 점에 길이 인 경우
			float cen_x = OutputTensor[i * channelStride];
			float cen_y = OutputTensor[i * channelStride + 1];

			results.Add(cen_x);							// center X
			results.Add(cen_y);							// center y

			UE_LOG(LogTemp, Warning, TEXT("Center: %f, %f"), cen_x, cen_y);
		}
	}

	if (results.Num() > 0) {
		UE_LOG(LogTemp, Log, TEXT("Results created successfully. Length of results: %d"), results.Num());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Results array is empty."));
	}

	UE_LOG(LogTemp, Log, TEXT("Results created successfully."));
}