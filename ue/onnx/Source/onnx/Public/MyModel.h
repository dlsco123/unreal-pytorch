// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "MyModel.generated.h"

UCLASS()
class ONNX_API AMyModel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyModel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	


	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		class UNeuralNetwork* myModel;// 에디터에서 직접 넣어주기
	UPROPERTY(EditAnywhere)
		class UMyNeuralNetwork* myNetwork; 
	
	// AC
	UPROPERTY(EditAnywhere)
		class UAC_Gen* objGenerator; //에디터에서 직접 넣어주기

	// Setting
	UPROPERTY(EditAnywhere, Category="Settings")
		float zPose = 50;

	// Data
	UPROPERTY(EditAnywhere)
		class UTexture2D* image_test;
	UPROPERTY(EditAnywhere)
		class UFileMediaSource* video_test;

	// Result
	UPROPERTY(EditAnywhere)
		TArray<float> result_arr;

	// Debug
	void AMyModel::SaveFloatArrayAsPNG(const TArray<float>& imageData, int32 width, int32 height, const FString& filePath);

	void SetModel(UNeuralNetwork* model);
	void RunModel();

	TArray<float> TextureToArray(UTexture2D* image);
	void GetImage();
};
