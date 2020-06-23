cmake_minimum_required(VERSION 3.5)
project(go_straight_and_turn)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(tf2 REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

include_directories(
  include
)
add_library(GoStraight
  src/GoCMD.cpp
  src/GoStraight.cpp
)
ament_target_dependencies(GoStraight rclcpp geometry_msgs nav_msgs)

add_library(GoTurn
  src/GoCMD.cpp
  src/GoTurn.cpp
)
ament_target_dependencies(GoTurn rclcpp geometry_msgs nav_msgs tf2)

add_executable(go_straight_node
  src/go_straight.cpp
)
ament_target_dependencies(go_straight_node rclcpp)
target_link_libraries(go_straight_node
  GoStraight
)

add_executable(go_turn_node
  src/go_turn.cpp
)
ament_target_dependencies(go_turn_node rclcpp)
target_link_libraries(go_turn_node
  GoTurn
)

install(TARGETS
  GoStraight
  GoTurn
  go_straight_node
  go_turn_node
  DESTINATION lib/${PROJECT_NAME})

ament_package()
