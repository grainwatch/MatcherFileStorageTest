// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>
#include <string>

void lol_write(std::string filename, cv::DescriptorMatcher* matcher, cv::NormTypes normType) {
	cv::FileStorage* fs = new cv::FileStorage(filename, cv::FileStorage::WRITE);
	std::vector<cv::Mat> trainDesc = matcher->getTrainDescriptors();
	*fs << "normType" << normType;
	std::string keyName = "trainDesc_";
	for (int i = 0; i < trainDesc.size(); i++) {
		*fs << keyName + std::to_string(i) << trainDesc[i];
	}
	fs->release();
}

int main()
{
	std::cout << "Test started.";
	cv::Mat img = cv::imread("test.jpg");
	cv::Mat ninja = cv::imread("test2.png");
	std::shared_ptr<cv::ORB> orb = cv::ORB::create(10);
	std::vector<cv::KeyPoint> kps1, kps2;
	cv::Mat des1, des2;
	orb->detectAndCompute(img, cv::noArray(), kps1, des1);
	orb->detectAndCompute(ninja, cv::noArray(), kps2, des2);
	std::cout << "found kps: " << kps1.size() << std::endl;
	std::cout << "desc dim: " << des1.rows << "x" << des1.cols << std::endl;


	std::shared_ptr<cv::DescriptorMatcher> bfMatcher = cv::FlannBasedMatcher::create();
	std::vector<cv::Mat>* decs = new std::vector<cv::Mat>();
	decs->push_back(des1);
	decs->push_back(des2);
	bfMatcher->add(*decs);
	lol_write("test_f.yml", bfMatcher.get(), cv::NormTypes::NORM_HAMMING);
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
