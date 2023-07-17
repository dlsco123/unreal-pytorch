// Fill out your copyright notice in the Description page of Project Settings.


#include "MyNeuralNetwork.h"

#include <fstream>
#include <iostream>
#include <array>
#include <string>
#include <filesystem>

using namespace std;
using namespace cv;

UMyNeuralNetwork::UMyNeuralNetwork()
{
	Network = nullptr;
}

void UMyNeuralNetwork::URunModel(TArray<float>& image, TArray<uint8>& results)
{
	if (Network == nullptr || !Network->IsLoaded()) {
		return;
	}


}