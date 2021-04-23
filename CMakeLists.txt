cmake_minimum_required(VERSION 3.4.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(ANDROID_STL gnustl_static)

project(gdmod VERSION 1.0.0)

add_subdirectory(code)

install(TARGETS gdmod LIBRARY DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/gd/lib/armeabi-v7a)
install(CODE "execute_process(COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/build-apk.sh)")
