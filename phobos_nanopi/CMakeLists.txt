cmake_minimum_required(VERSION 2.8.3)
project(phobos_nanopi)

# set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -pthread -lwiringPi -fpermissive")
set(CMAKE_CXX_FLAGS "-std=c++11")

# FIND_LIBRARY(WIRINGPI_LIBRARY wiringPi /home/agh/ProgramFiles/WiringOP/wiringPi)

find_package(catkin REQUIRED COMPONENTS
    roscpp
    tf
    cv_bridge
    image_transport
)

find_package(OpenCV 3.0.0 REQUIRED)

include_directories(SYSTEM ${OpenCV_INCLUDE_DIRS} ${catkin_INCLUDE_DIRS})

catkin_package()

# add_executable(ov2640_driver
#     src/ov2640_driver/Main.cpp
#     src/ov2640_driver/arducam_arch_raspberrypi.cpp
#     src/ov2640_driver/arducam.cpp
#     )
# add_dependencies(ov2640_driver wiringPi)
# target_link_libraries(ov2640_driver ${OpenCV_LIBRARIES} ${catkin_LIBRARIES} ${WIRINGPI_LIBRARY})

add_executable(usb_cam_driver
    src/usb_cam_driver/Main.cpp
    )
target_link_libraries(usb_cam_driver ${OpenCV_LIBRARIES} ${catkin_LIBRARIES})
