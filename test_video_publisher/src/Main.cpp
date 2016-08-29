#include <ros/ros.h>

#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>

#include <std_msgs/Header.h>
#include <sensor_msgs/Image.h>

#define WIDTH 320
#define HEIGHT 240

int main(int argc, char** argv){
	ros::init(argc, argv, "test_video_publisher");
	ros::NodeHandle nh;

	cv::Mat frame(HEIGHT, WIDTH, CV_8UC3);

	ros::Rate loop_rate(10);

	image_transport::ImageTransport it(nh);
    	image_transport::Publisher pub_img = it.advertise("/test/image_stream",1);
	
	sensor_msgs::ImagePtr img;
    	std_msgs::Header header;
		header.seq = 0;
        	header.frame_id = "test_image";


	int x = 0;

	while(ros::ok()){
		for(int i = 0; i < HEIGHT; i++){
			for(int j=0; j < WIDTH; j++){
				*(frame.data + i*WIDTH*3 + j*3 + 0) = 255 -(j + x) % 256;
				*(frame.data + i*WIDTH*3 + j*3 + 1) = 255 -(j + x) % 256;
				*(frame.data + i*WIDTH*3 + j*3 + 2) = 255 -(j + x) % 256;
			}
		}

		if(x%256 == 0) ROS_INFO("X=0");
		x += 1;

		header.seq++;
        	header.stamp = ros::Time::now();
		
		img = cv_bridge::CvImage(header, "bgr8", frame).toImageMsg();
       	 	pub_img.publish(img);
		cv::waitKey(1);	

	
		//ros::spinOnce();
		loop_rate.sleep();
	}

	return 0;
}
			
