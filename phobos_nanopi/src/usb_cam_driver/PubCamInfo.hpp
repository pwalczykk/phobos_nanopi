#ifndef PUB_msg_HPP_
#define PUB_msg_HPP_

#include <ros/ros.h>
#include <sensor_msgs/CameraInfo.h>

class PubCamInfo{
    ros::NodeHandle *nh;
    ros::Publisher pub;

public:
    sensor_msgs::CameraInfo msg;

    sensor_msgs::ImagePtr img;
    std_msgs::Header* header_ptr;

public:
    PubCamInfo(int cam_num, std_msgs::Header *header_ptr, int width, int height, ros::NodeHandle *nh){
        std::ostringstream camera_name;
        camera_name << "camera" << cam_num;

        this->nh = nh;
        this->pub = nh->advertise<sensor_msgs::CameraInfo>("/rover/" + camera_name.str() + "/camera_info", 100);

        this->header_ptr = header_ptr;

        this->msg.height = height;
        this->msg.width = width;

        this->msg.roi.x_offset = 0;
        this->msg.roi.y_offset = 0;
        this->msg.roi.height = 0;
        this->msg.roi.width = 0;
        this->msg.roi.do_rectify = false;


    }

    void PublishInfo()
    {
        this->msg.header = *this->header_ptr;

        pub.publish(msg);
    }
};

#endif
