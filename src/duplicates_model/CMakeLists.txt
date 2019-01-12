cmake_minimum_required(VERSION 3.1)

set(TARGET_NAME duplicates_model)

find_package(Qt5 COMPONENTS Core REQUIRED)

set(SRC duplicatesmodel.cpp)
set(HDR duplicatesmodel.h)

add_library(${TARGET_NAME} ${SRC} ${HDR})
target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${TARGET_NAME} PUBLIC duplicate_finder PRIVATE Qt5::Core)
