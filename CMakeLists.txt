file(GLOB SOURCES src/*.cpp)

cmake_minimum_required(VERSION 3.17)

project(segment)

add_subdirectory(pybind11)

find_package(OpenCV REQUIRED)
find_package(PythonLibs REQUIRED)
find_package(OpenMP REQUIRED)
set(CMAKE_CXX_STANDARD 17)

include_directories(segment include)
include_directories(${PYTHON_INCLUDE_DIRS})

pybind11_add_module(segment SHARED ${SOURCES})
target_link_libraries(segment PRIVATE ${PYTHON_LIBRARIES} ${OpenCV_LIBS} OpenMP::OpenMP_CXX)

#add_executable(segment ${SOURCES})

