cmake_minimum_required(VERSION 3.19)
project(QCInspection)

set(CMAKE_CXX_STANDARD 14)

# opencv
find_package(OpenCV 4.5.2 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

find_package(OpenMP)
if (OPENMP_FOUND)
    message("OPENMP FOUND")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif ()


add_executable(QCInspection main.cpp templateMatching.cpp)
target_link_libraries(QCInspection ${OpenCV_LIBS})