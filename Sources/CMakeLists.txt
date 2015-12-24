cmake_minimum_required(VERSION 3.3)
project(TextureMapping)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

#set everything up for the import of Qt libraries
set(CMAKE_AUTOMOC ON)
#set(CMAKE_PREFIX_PATH D:/Qt/Qt5.5.1/MinGW/5.5/mingw492_32)
set(CMAKE_PREFIX_PATH "D:/Qt/Qt5.5.1/5.5/mingw492_32")

#Create the binary in a subfolder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

set(SOURCE_FILES main.cpp)
file(GLOB SRCS *.cpp *.h)

#import Qt libraries
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Core REQUIRED)

#include Qt headers
include_directories(${Qt5Widgets_INCLUDES})

add_executable(TextureMapping ${SRCS})

#use the required modules
qt5_use_modules(TextureMapping Widgets Core Gui)
