#ifndef IMAGEPUBLISHER_HPP_
#define IMAGEPUBLISHER_HPP_

#include "CameraHandler.hpp"

#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>

#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <sensor_msgs/CameraInfo.h>
#include <std_msgs/Header.h>

#include <sstream>

class ImagePublisher : public CameraHandler{
    ros::NodeHandle nh;
    image_transport::ImageTransport* it;
    image_transport::Publisher pub_img;

protected:
    sensor_msgs::ImagePtr img;
    std_msgs::Header header;

public:
    ImagePublisher(int cam_num) : CameraHandler(0){
        std::ostringstream oss_camera;
        oss_camera << "/rover/camera" << cam_num << "/image";

        it = new image_transport::ImageTransport(nh);
        pub_img = it->advertise(oss_camera.str(), 1);

        header.seq = 0;
        header.frame_id = oss_camera.str();

    }

    void PublishImage(){
        header.seq++;
        header.stamp = ros::Time::now();

        CameraHandler::Capture();
        cv::waitKey(1);

        img = cv_bridge::CvImage(header, "bgr8", CameraHandler::frame).toImageMsg();

        pub_img.publish(img);
    }
};

#endif
