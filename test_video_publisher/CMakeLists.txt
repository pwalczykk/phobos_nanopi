cmake_minimum_required(VERSION 2.8.3)
project(test_video_publisher)

find_package(catkin REQUIRED COMPONENTS
	roscpp
	cv_bridge
	image_transport
)

find_package(OpenCV 3.0.0 REQUIRED)

include_directories(SYSTEM ${OpenCV_INCLUDE_DIRS} ${catkin_INCLUDE_DIRS})

catkin_package()

add_executable(test_video_publisher 
	src/Main.cpp
)
target_link_libraries(test_video_publisher ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})

