#include "CameraHandler.hpp"
#include "ImagePublisher.hpp"

int main(int argc, char** argv){


    ros::init(argc, argv, "titanum_camera_driver");
    ros::NodeHandle nh;

    int cam_num1;
    nh.param("/camera_number", cam_num1, 0);

    ImagePublisher cam1(cam_num1);
    cam1.CameraHandler::Init();
    cam1.CameraHandler::Set(320, 240, 30);

    ros::Rate loop_rate(10);
    while(ros::ok()){
        cam1.PublishImage();
        loop_rate.sleep();
    }

    cam1.CameraHandler::Release();
    return 0;
}
