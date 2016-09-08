#ifndef SYNCHRONIZER_HPP_
#define SYNCHRONIZER_HPP_

#include <ros/ros.h>
#include <std_msgs/Bool.h>
#include <unistd.h>

class Synchronizer{
    ros::NodeHandle *nh;
    ros::Subscriber sub;
public:
    bool START_FLAG;

public:
    Synchronizer(std::string topic, ros::NodeHandle *nh){
        this->nh = nh;
        this->sub = nh->subscribe(topic, 100, &Synchronizer::MsgInterrupt, this);
        this->START_FLAG = 0;
    }

    void MsgInterrupt(const std_msgs::Bool msg){
        this->START_FLAG = msg.data;
    }

    void WaitForSynchro(int delay_ms){
        ros::Rate loop_rate(1000);
        while(ros::ok()){
            ros::spinOnce();
            if(START_FLAG == 1)
                break;
            loop_rate.sleep();
        }

        if(delay_ms > 0){
            usleep(delay_ms*1000);
        }
    }
};

#endif
