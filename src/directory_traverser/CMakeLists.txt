cmake_minimum_required(VERSION 3.1)

set(TARGET_NAME directory_traverser)

find_package(Qt5 COMPONENTS Core REQUIRED)

set(SRC directorytraverser.cpp)
set(HDR idirectorytraverser.h
        directorytraverser.h)

add_library(${TARGET_NAME} ${SRC} ${HDR})
target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${TARGET_NAME} PRIVATE Qt5::Core)
