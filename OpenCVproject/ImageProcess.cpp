#include <iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2\opencv.hpp>
#include "ImageProcess.h"
using namespace cv;
Image::Image()
{

}
Image::~Image()
{

}
void Image::SetMatInput(Mat inputMat)
{
	this->input = inputMat;
}
void Image::SetMatOutput(Mat outputMat)
{
	this->output = outputMat;
}
Mat Image::GetMatInput()
{
	return input;
}
Mat Image::GetMatOutput()
{
	return output;
}
void BlackAndWhite( Image & image)
{
	try
	{
		Mat help; 
		cvtColor(image.GetMatInput(), help, CV_BGR2GRAY);
		image.SetMatOutput(help);
	}
	catch (...)
	{
		std::cout << "Error" << std::endl;
	}
}
Mat MakeKernel ()
{
	try
	{
		Mat kernel = (cv::Mat_<float>(3, 3)
			<<
			0.272, 0.534, 0.131,
			0.349, 0.686, 0.168,
			0.393, 0.769, 0.189);
		return kernel;
	}
	catch (...)
	{
		std::cout << "Error" << std::endl;
	}
}
void Sepia(Image & image)
{
	try
	{
		Mat Kernel = MakeKernel();
		Mat help;
		cv::transform(image.GetMatInput(), help, Kernel);
		image.SetMatOutput(help);
	}
	catch (...)
	{
		std::cout << "Error" << std::endl;
	}
}
Mat EdgeDetection(Image & image)
{
	Mat gray, dst, dst_abs;
	GaussianBlur(image.GetMatInput(), image.GetMatOutput(), Size(3, 3), 0, 0, BORDER_DEFAULT);
	cvtColor(image.GetMatInput(), gray, CV_RGB2GRAY);
	Laplacian(gray, dst, CV_16S, 3, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(dst, dst_abs);
	return dst_abs;
}
void Smooth(Image & image)
{
	Mat help;
	GaussianBlur(image.GetMatInput(), help, Size(5, 5), 3, 3);
	GaussianBlur(image.GetMatInput(),help, Size(5, 5), 3, 3);
	image.SetMatOutput(help);
}
void Britness(Image & image, int number)
{
	Mat help;
	image.GetMatInput().convertTo(help, -1, 1, number);
	image.SetMatOutput(help);
}
void Contrast(Image & image)
{
	int alfa, beta;
	image.GetMatOutput() = Mat::zeros(image.GetMatInput().size(), image.GetMatInput().type());
	std::cout << "*Enter the alpha value [1.0-3.0]:"; std::cin >> alfa;
	std::cout << "*Enter the beta value [0-100]:"; std::cin >> beta;
	for (int y = 0; y < image.GetMatInput().rows; y++)
	{
		for (int x = 0; x < image.GetMatInput().cols; x++)
		{
			for (int c =0; c< 3; c++)
			{
				image.GetMatOutput().at<Vec3b>(y, x)[c] = saturate_cast<uchar>(alfa*(image.GetMatInput().at<Vec3b>(y, x)[c]) + beta);
			}
		}
	}
}