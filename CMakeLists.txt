cmake_minimum_required(VERSION 3.5)
project(mapping)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(driver src/mapping_node.cpp)

target_link_libraries(driver GLEW)
target_link_libraries(driver glfw)
target_link_libraries(driver OpenGL::GL)

ament_target_dependencies(driver rclcpp std_msgs Eigen3)

file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp
                    ${PROJECT_SOURCE_DIR}/src/common/*.cpp)

target_sources(driver PRIVATE ${SRC_FILES})

target_include_directories(driver
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)

install(TARGETS
  driver
  DESTINATION lib/${PROJECT_NAME})

ament_package()