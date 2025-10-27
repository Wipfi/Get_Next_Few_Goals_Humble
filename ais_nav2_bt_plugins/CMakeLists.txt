cmake_minimum_required(VERSION 3.8)
project(ais_nav2_bt_plugins)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

find_package(ament_cmake REQUIRED)
find_package(behaviortree_cpp_v3 REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(rclcpp REQUIRED)

add_library(get_next_few_goals_bt SHARED
  src/get_next_few_goals.cpp)

target_include_directories(get_next_few_goals_bt PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

target_compile_definitions(get_next_few_goals_bt
  PRIVATE BT_PLUGIN_EXPORT)

ament_target_dependencies(get_next_few_goals_bt
  behaviortree_cpp_v3
  geometry_msgs
  rclcpp)

install(TARGETS get_next_few_goals_bt
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin)

install(DIRECTORY include/
  DESTINATION include)

install(FILES plugin.xml
  DESTINATION share/${PROJECT_NAME})

ament_export_dependencies(
  behaviortree_cpp_v3
  geometry_msgs
  rclcpp)
ament_export_include_directories(include)
ament_export_libraries(get_next_few_goals_bt)

ament_package()
