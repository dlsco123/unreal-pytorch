// NNI Plugin
#include "NeuralNetwork.h"

// Custom Class
#include "MyNeuralNetwork.h"
#include "AC_Gen.h"

//Open CV Plugin
#include "PreOpenCVHeaders.h"
#include "OpenCVHelper.h"
#include <ThirdParty/OpenCV/include/opencv2/imgproc.hpp>
#include <ThirdParty/OpenCV/include/opencv2/highgui/highgui.hpp>
#include <ThirdParty/OpenCV/include/opencv2/core.hpp>
#include "PostOpenCVHeaders.h"
#include <vector>

#include "Engine/Texture2D.h"

#include "MyModel.h"

using namespace std;
using namespace cv;

// Sets default values
AMyModel::AMyModel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	objGenerator = CreateDefaultSubobject<UAC_Gen>(TEXT("ObjectPool"));
}

// Called when the game starts or when spawned
void AMyModel::BeginPlay()
{
	Super::BeginPlay();

	SetModel(myModel);
}

// Called every frame
void AMyModel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RunModel();
}

void AMyModel::SetModel(UNeuralNetwork* model)
{
	UE_LOG(LogTemp, Warning, TEXT("SetModel _ Start"));

	model->AddToRoot();

	myNetwork = NewObject<UMyNeuralNetwork>();
	model->SetDeviceType(ENeuralDeviceType::GPU);
	myNetwork->Network = model;
}

void AMyModel::RunModel()
{
	UE_LOG(LogTemp, Warning, TEXT("RunModel _ Start"));

	//이미지를 얻는다
	//GetImage();
	TArray<float> imgArray = TextureToArray(image_test);

	if (imgArray.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("imgArray Changing failed"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("RunModel _ imgArray : %f, len : %d"), imgArray[0], imgArray.Num());

	myNetwork->URunModel(imgArray, result_arr);

	// 오브젝트를 생성한다.
	int num_object = result_arr.Num() / 2;
	
	for (int i = 0; i < num_object; i++)
	{
		FVector pose = FVector(result_arr[i * num_object], result_arr[i * num_object + 1], zPose);
		objGenerator->GenObject(i, pose);
	}
	
	// 오브젝트 다시 회수
}

TArray<float> AMyModel::TextureToArray(UTexture2D* image) // 파라미터 의미 없음. 기존 이미지 바로 로드해서 사용하는 방법
{
	TArray<float> result;
	
	FString contentDirectory = FPaths::ProjectContentDir();
	FString relativeImagePath = FPaths::Combine(contentDirectory, TEXT("Data/image.png"));
	std::string imagePath(TCHAR_TO_UTF8(*relativeImagePath));

	cv::Mat Img = cv::imread(imagePath, cv::IMREAD_COLOR);  // 이미지 파일을 cv::Mat 형태로 불러옵니다.

	if (Img.empty())
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load image at %s"), *relativeImagePath);
		return result;
	}

	cv::Vec3b firstPixel = Img.at<cv::Vec3b>(0, 0);
	UE_LOG(LogTemp, Warning, TEXT("First pixel BGR: %d, %d, %d"), firstPixel[0], firstPixel[1], firstPixel[2]);

	// YOLOv5의 입력 이미지 사이즈에 맞게 이미지를 리사이즈
	cv::Mat resizedImg;
	cv::resize(Img, resizedImg, cv::Size(640, 640));  // 여기서는 예시로 640x640으로 설정했습니다.

	result.Reserve(resizedImg.rows * resizedImg.cols * resizedImg.channels());

	for (int i = 0; i < resizedImg.rows; ++i)
	{
		for (int j = 0; j < resizedImg.cols; ++j)
		{
			cv::Vec3b Pixel = resizedImg.at<cv::Vec3b>(i, j);  // BGR format으로 읽어옵니다.
			result.Add(Pixel[2] / 255.0f);  // R
			result.Add(Pixel[1] / 255.0f);  // G
			result.Add(Pixel[0] / 255.0f);  // B

			// Add logs to check values
			if (i == 0 && j == 0)
			{
				UE_LOG(LogTemp, Warning, TEXT("First pixel RGB in array: %f, %f, %f"),
					result[result.Num() - 3], result[result.Num() - 2], result[result.Num() - 1]);
			}
		}
	}

	return result;
}

void AMyModel::GetImage()
{
	// 이미지를 에셋에서 불러온다.

	//imgae_test 변수에 저장한다.


	//Todo -> 영상에서 한프레임씩 받아온다.
}