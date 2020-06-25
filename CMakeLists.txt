cmake_minimum_required(VERSION 2.8.3)
project(go_straight_and_turn)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  nav_msgs
  roscpp
  rospy
  tf2
)

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if your package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
  INCLUDE_DIRS include
  LIBRARIES GoStraight GoTurn
  CATKIN_DEPENDS geometry_msgs nav_msgs roscpp rospy tf2
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
  include ${catkin_INCLUDE_DIRS}
# include
  ${catkin_INCLUDE_DIRS}
)

## Declare a C++ library

add_library(GoStraight
  src/GoStraight.cpp
  src/GoCMD.cpp
)
add_dependencies(GoStraight ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(GoStraight
  ${catkin_LIBRARIES}
)

add_executable(go_straight
  src/go_straight.cpp
)
add_dependencies(go_straight ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} GoStraight)
target_link_libraries(go_straight
  ${catkin_LIBRARIES}
  GoStraight
)

add_library(GoTurn
  src/GoTurn.cpp
  src/GoCMD.cpp
)
add_dependencies(GoTurn ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(GoTurn
  ${catkin_LIBRARIES}
)

add_executable(go_turn
  src/go_turn.cpp
)
add_dependencies(go_turn ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} GoTurn)
target_link_libraries(go_turn
  ${catkin_LIBRARIES}
  GoTurn
)
