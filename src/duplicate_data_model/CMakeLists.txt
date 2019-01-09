cmake_minimum_required(VERSION 3.1)

set(TARGET_NAME duplicate_data_model)

find_package(Qt5 COMPONENTS Core REQUIRED)

set(SRC duplicatedatamodel.cpp)
set(HDR duplicatedatamodel.h)

add_library(${TARGET_NAME} ${SRC} ${HDR})
target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${TARGET_NAME} PRIVATE Qt5::Core duplicate_finder)
