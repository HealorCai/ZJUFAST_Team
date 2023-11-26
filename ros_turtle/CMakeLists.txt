cmake_minimum_required(VERSION 3.0.2) #指定构建此项目所需的CMake的最低版本3.0.2
project(ros_turtle) #定义了项目名称为ros_turtle
# add_compile_options(-std=c++11) #指定使用C++11标准来编译代码

find_package(Eigen3 REQUIRED) #查找并包含了Eigen3库，REQUIRED关键字表示Eigen3是构建此项目的必需依赖

find_package(catkin REQUIRED COMPONENTS
  roscpp
  turtlesim
  geometry_msgs
) #查找catkin和其他几个ROS依赖项，包括roscpp turtlesim geometry_msgs

catkin_package(
  CATKIN_DEPENDS geometry_msgs roscpp turtlesim
) #声明了这个ROS包的catkin特定依赖项

include_directories(
    include
    ${catkin_INCLUDE_DIRS}
    ${Eigen3_INCLUDE_DIRS}
) #包括了编译时需要的头文件目录

add_executable(turtle_todo src/turtle_todo.cpp ) #添加可执行文件turtle_node，由src/turtle.cpp源文件构建而成

#将前面定义的可执行文件turtle_node链接到catkin的库
target_link_libraries(turtle_todo 
  ${catkin_LIBRARIES}
) 

