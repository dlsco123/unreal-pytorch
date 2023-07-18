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
	//�̹����� ��´�
	GetImage();
	TArray<float> imgArray = TextureToArray(image_test);

	myNetwork->URunModel(imgArray, result_arr);

	// ������Ʈ�� �����Ѵ�.
	
}

TArray<float> AMyModel::TextureToArray(UTexture2D* image) // �Ķ���� �ǹ� ����. ���� �̹��� �ٷ� �ε��ؼ� ����ϴ� ���
{
	TArray<float> result;
	
	FString contentDirectory = FPaths::ProjectContentDir();
	FString relativeImagePath = FPaths::Combine(contentDirectory, TEXT("Data/images.jpg"));
	std::string imagePath(TCHAR_TO_UTF8(*relativeImagePath));

	cv::Mat Img = cv::imread(imagePath, cv::IMREAD_COLOR);  // �̹��� ������ cv::Mat ���·� �ҷ��ɴϴ�.

	result.Reserve(Img.rows * Img.cols * Img.channels());

	for (int i = 0; i < Img.rows; ++i)
	{
		for (int j = 0; j < Img.cols; ++j)
		{
			cv::Vec3b Pixel = Img.at<cv::Vec3b>(i, j);  // BGR format���� �о�ɴϴ�.
			result.Add(Pixel[2] / 255.0f);  // R
			result.Add(Pixel[1] / 255.0f);  // G
			result.Add(Pixel[0] / 255.0f);  // B
		}
	}

	return result;
}

void AMyModel::GetImage()
{
	// �̹����� ���¿��� �ҷ��´�.

	//imgae_test ������ �����Ѵ�.


	//Todo -> ���󿡼� �������Ӿ� �޾ƿ´�.
}