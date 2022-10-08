
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

///////////////////////////////////////////////////////////////////////////////////////////////////
void playVideo(const char * path) {

    cv::VideoCapture capVideo;
    cv::Mat imgFrame;

    capVideo.open(path);
    capVideo.read(imgFrame);


    char chCheckForEscKey = 0;


    while (capVideo.read(imgFrame)) {
        resize(imgFrame, imgFrame, cv::Size(1280, 720));
        cv::imshow("imgFrame", imgFrame);
        cv::moveWindow("imgFrame", 20, 20);
        if (cv::waitKey(25) >= 0)
            break;

    }

    cv::destroyAllWindows();
    
}

#pragma once
