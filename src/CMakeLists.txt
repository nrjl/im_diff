cmake_minimum_required(VERSION 2.8.3)
project(im_diff)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(catkin REQUIRED COMPONENTS
    roscpp
    rospy
    std_msgs
    sensor_msgs
    image_transport)

catkin_package()

include_directories(
    include
    ${catkin_INCLUDE_DIRS}
    )

add_executable(im_diff im_diff.cpp)
target_link_libraries(im_diff ${catkin_LIBRARIES})

add_executable(im_shrink im_shrink.cpp)
target_link_libraries(im_shrink ${catkin_LIBRARIES})
