#ifndef IMAGEPUBLISHER_HPP_
#define IMAGEPUBLISHER_HPP_

#include "ov2640_driver.hpp"

#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>

#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <sensor_msgs/CameraInfo.h>
#include <std_msgs/Header.h>

#define IMG_BUFF_SIZE (320*240*3)

class ImagePublisher : public ov2640_driver{
    ros::NodeHandle *nh;
    image_transport::ImageTransport* it;
    image_transport::Publisher pub_img;

protected:
    cv::Mat img_buffor;
    sensor_msgs::ImagePtr img;
    std_msgs::Header header;

public:
    ImagePublisher(std::string publisher_topic, ros::NodeHandle *nh) : ov2640_driver(){
        this->nh = nh;

        it = new image_transport::ImageTransport(*nh);
        pub_img = it->advertise(publisher_topic, 1);

        header.seq = 0;
        header.frame_id = "ip";
    }

    void Init(){
        ov2640_driver::Init();
    }

    void PublishImage(){
        header.seq++;
        header.stamp = ros::Time::now();

        ov2640_driver::Capture();

        for(int i = 0; i < IMG_BUFF_SIZE; i++){
            *(img_buffor.data + i) = ov2640_driver::buffer[i];
        }

        img = cv_bridge::CvImage(header, "bgr8", img_buffor).toImageMsg();
        pub_img.publish(img);
    }
};

#endif
