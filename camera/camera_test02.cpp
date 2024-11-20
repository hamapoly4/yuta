#include <opencv2/opencv.hpp>

int main() {
 cv::Mat img;

 img = cv::imread("3.jpg");

 cv::imshow("title", img);
 cv::waitKey(0);

 return 0;
}
