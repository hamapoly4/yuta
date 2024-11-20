#include <opencv2/opencv.hpp>
#include <iostream>

int main()
{
	// V4L2
	cv::VideoCapture cap;
	cap.open("/dev/video0", cv::CAP_V4L2);

	if (!cap.isOpened())
	{
		std::cerr << "Error : don't open camera." << std::endl;
		return -1;
	}

	cv::Mat frame;
	while (true)
	{
		cap >> frame;
		if (frame.empty())
		{
			printf("don't capture frame!!\n");
			break;
		}

		cv::imshow("Camera", frame);

		if (cv::waitKey(1) == 'q')
		{
			break;
		}
	}

	cap.release();
	cv::destroyAllWindows();
	return 0;
}
