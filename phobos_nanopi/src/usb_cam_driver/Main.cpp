#include "CameraHandler.hpp"
#include "ImagePublisher.hpp"
#include "Synchronizer.hpp"

int main(int argc, char** argv){


    ros::init(argc, argv, "usb_cam_driver");
    ros::NodeHandle nh("~");
    ros::Rate loop_rate(10);

    int cam_num1;
    nh.param("camera_number", cam_num1, 0);

    ROS_WARN("%d", cam_num1);

    int delay_ms;
    nh.param("delay_ms", delay_ms, 0);

    ImagePublisher cam1(cam_num1);
    cam1.CameraHandler::Init();
    // cam1.CameraHandler::Set(320, 240, 30);

    Synchronizer synchronizer("/rover/camera/stereo_synchro", &nh);
    synchronizer.WaitForStart(delay_ms);


    while(ros::ok()){
        cam1.PublishImage();
        loop_rate.sleep();
    }

    cam1.CameraHandler::Release();
    return 0;
}
