#include "CameraHandler.hpp"
#include "ImagePublisher.hpp"
#include "Synchronizer.hpp"
#include "PubCamInfo.hpp"

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
    cam1.CameraHandler::Set(320, 240, 10);


    Synchronizer synchronizer("/rover/camera/stereo_synchro", &nh);
    synchronizer.WaitForSynchro(delay_ms);


    // CameraInfo
    PubCamInfo cam1_info(cam_num1, &cam1.header, 320, 240, &nh);

    double K[9];
    double R[9];
    double P[12];
    int binning_x = 0;
    int binning_y = 0;

    nh.param("K0", cam1_info.msg.K[0], (double)0.0);
    nh.param("K1", cam1_info.msg.K[1], (double)0.0);
    nh.param("K2", cam1_info.msg.K[2], (double)0.0);
    nh.param("K3", cam1_info.msg.K[3], (double)0.0);
    nh.param("K4", cam1_info.msg.K[4], (double)0.0);
    nh.param("K5", cam1_info.msg.K[5], (double)0.0);
    nh.param("K6", cam1_info.msg.K[6], (double)0.0);
    nh.param("K7", cam1_info.msg.K[7], (double)0.0);
    nh.param("K8", cam1_info.msg.K[8], (double)0.0);

    nh.param("R0", cam1_info.msg.R[0], (double)0.0);
    nh.param("R1", cam1_info.msg.R[1], (double)0.0);
    nh.param("R2", cam1_info.msg.R[2], (double)0.0);
    nh.param("R3", cam1_info.msg.R[3], (double)0.0);
    nh.param("R4", cam1_info.msg.R[4], (double)0.0);
    nh.param("R5", cam1_info.msg.R[5], (double)0.0);
    nh.param("R6", cam1_info.msg.R[6], (double)0.0);
    nh.param("R7", cam1_info.msg.R[7], (double)0.0);
    nh.param("R8", cam1_info.msg.R[8], (double)0.0);

    nh.param("P0", cam1_info.msg.P[0], (double)0.0);
    nh.param("P1", cam1_info.msg.P[1], (double)0.0);
    nh.param("P2", cam1_info.msg.P[2], (double)0.0);
    nh.param("P3", cam1_info.msg.P[3], (double)0.0);
    nh.param("P4", cam1_info.msg.P[4], (double)0.0);
    nh.param("P5", cam1_info.msg.P[5], (double)0.0);
    nh.param("P6", cam1_info.msg.P[6], (double)0.0);
    nh.param("P7", cam1_info.msg.P[7], (double)0.0);
    nh.param("P8", cam1_info.msg.P[8], (double)0.0);
    nh.param("P9", cam1_info.msg.P[9], (double)0.0);
    nh.param("P10", cam1_info.msg.P[10], (double)0.0);
    nh.param("P11", cam1_info.msg.P[11], (double)0.0);

    nh.param("binning_x", binning_x, (int)0);   cam1_info.msg.binning_x = binning_x;
    nh.param("binning_y", binning_y, (int)0);   cam1_info.msg.binning_y = binning_y;

    while(ros::ok()){
        if(synchronizer.START_FLAG){
            cam1.PublishImage();
            cam1_info.PublishInfo();
            // ROS_WARN("Info publisher");
        }
        loop_rate.sleep();
    }

    cam1.CameraHandler::Release();
    return 0;
}
