#include <opencv2/opencv.hpp>
#include <stdio.h>

int main() 
{
    cv::VideoCapture cap("/dev/video0", cv::CAP_V4L2); // V4L2を指定してカメラを開く

    if (!cap.isOpened())
    {
        printf("don't open camera!!\n");
        return -1;
    }

    // カメラ設定の確認と手動でFPSを設定

    //cap.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('Y', 'U', '1', '2')); // ピクセルフォーマットをBA81に設定


    cv::Mat frame;
    while (true)
    {
        cap >> frame; // フレームの取得
        if (frame.empty())
        {
            printf("Empty frame\n");
            break;
        }
        cv::imshow("Camera", frame); // フレームを表示

        // 'q' キーが押されたらループを終了
        if (cv::waitKey(1) == 'q')
        {
            break;
        }
    }
    cap.release(); // カメラデバイスを解放
    cv::destroyAllWindows();
    return 0;
}
