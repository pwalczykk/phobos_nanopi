#ifndef GETIMAGE_HPP_
#define GETIMAGE_HPP_

#include <opencv2/opencv.hpp>
#include <unistd.h>

class CameraHandler{
    cv::VideoCapture cap;

protected:
    cv::Mat frame;
    int cam_num;

public:
    CameraHandler(int cam_num){
        this->cam_num = cam_num;
        cap = cv::VideoCapture();
    }

    void Init(){
        while(!cap.open(cam_num)){
            usleep(10000);
        }
    }

    void Release(){
        cap.release();
    }

    void Set(int res_x, int res_y, int fps){
        // cap.set(CV_CAP_PROP_FRAME_WIDTH,res_x);
        // cap.set(CV_CAP_PROP_FRAME_HEIGHT,res_y);
        // cap.set(CV_CAP_PROP_FPS,fps);
    }

    void Capture(){
        cap >> frame;
    }
};

#endif
