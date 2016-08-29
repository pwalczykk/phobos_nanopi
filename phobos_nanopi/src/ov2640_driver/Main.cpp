#include <ros/ros.h>
#include "ImagePublisher.hpp"

int main(int argc, char** argv){

    ros::init(argc, argv, "ov2640_driver");
    ros::NodeHandle nh;
    ros::Rate loop_rate(10);

    std::string topic;
    nh.param("topic", topic, (std::string)"/nanopi/ov2640_cam/image");

    ImagePublisher cam(topic, &nh);

    cam.Init();

    while(ros::ok()){
        cam.PublishImage();
        loop_rate.sleep();
    }

    return 0;
}
