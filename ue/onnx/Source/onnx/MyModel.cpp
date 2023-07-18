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

#include "MyModel.h"

using namespace std;
using namespace cv;

// Sets default values
AMyModel::AMyModel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
	model->AddToRoot();

	myNetwork = NewObject<UMyNeuralNetwork>();
	model->SetDeviceType(ENeuralDeviceType::GPU);
	myNetwork->Network = model;
}

void AMyModel::RunModel()
{
	//이미지를 얻는다
	GetImage();
	TArray<float> imgArray = TextureToArray(image_test);

	myNetwork->URunModel(imgArray, result_arr);

	// 오브젝트를 생성한다.
	
}

TArray<float> AMyModel::TextureToArray(UTexture2D* image) // 파라미터 의미 없음. 기존 이미지 바로 로드해서 사용하는 방법
{
	TArray<float> result;
	
	FString contentDirectory = FPaths::ProjectContentDir();
	FString relativeImagePath = FPaths::Combine(contentDirectory, TEXT("Data/images.jpg"));
	std::string imagePath(TCHAR_TO_UTF8(*relativeImagePath));

	cv::Mat Img = cv::imread(imagePath, cv::IMREAD_COLOR);  // 이미지 파일을 cv::Mat 형태로 불러옵니다.

	result.Reserve(Img.rows * Img.cols * Img.channels());

	for (int i = 0; i < Img.rows; ++i)
	{
		for (int j = 0; j < Img.cols; ++j)
		{
			cv::Vec3b Pixel = Img.at<cv::Vec3b>(i, j);  // BGR format으로 읽어옵니다.
			result.Add(Pixel[2] / 255.0f);  // R
			result.Add(Pixel[1] / 255.0f);  // G
			result.Add(Pixel[0] / 255.0f);  // B
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