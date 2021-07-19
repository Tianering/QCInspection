cmake_minimum_required(VERSION 3.19)
project(QCInspection)

set(CMAKE_CXX_STANDARD 14)

# opencv
find_package(OpenCV 4.5.2 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(QCInspection main.cpp templateMatching.cpp)
target_link_libraries(QCInspection ${OpenCV_LIBS})