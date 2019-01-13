cmake_minimum_required(VERSION 3.1)

set(TARGET_NAME duplicate_finder)

find_package(Qt5 COMPONENTS Core Concurrent REQUIRED)

set(SRC duplicatefinder.cpp
        concurrentduplicatefinder.cpp)
set(HDR iduplicatefinder.h
        duplicatefinder.h
        concurrentduplicatefinder.h)

add_library(${TARGET_NAME} ${SRC} ${HDR})
target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${TARGET_NAME}
PUBLIC
        file_comparator
        Qt5::Core
PRIVATE
        Qt5::Concurrent
)
