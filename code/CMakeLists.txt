cmake_minimum_required(VERSION 3.10.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(ANDROID_STL gnustl_static)

project(gdmod VERSION 1.0.0)

add_library(gdmod SHARED
  src/base/module.cpp
  src/base/hooks.cpp
  src/base/hook_handler.cpp
  src/aura.cpp
  src/modules/default.cpp
  src/modules/icon.cpp
  src/modules/icon/savedata.cpp
  src/modules/icon/add_btns.cpp)

target_include_directories(gdmod PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/external/cocos2d/
  ${CMAKE_CURRENT_SOURCE_DIR}/external/fmod/

  ${CMAKE_CURRENT_SOURCE_DIR}/external/cocos2d/incl/cocos2dx
  ${CMAKE_CURRENT_SOURCE_DIR}/external/cocos2d/incl/cocos2dx/include
  ${CMAKE_CURRENT_SOURCE_DIR}/external/cocos2d/incl/cocos2dx/kazmath/include
  ${CMAKE_CURRENT_SOURCE_DIR}/external/cocos2d/incl/cocos2dx/platform/android
  ${CMAKE_CURRENT_SOURCE_DIR}/external/cocos2d/incl/extensions/

  ${CMAKE_CURRENT_SOURCE_DIR}/external/Dobby/include

  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

find_package(Git)
execute_process(COMMAND
  "${GIT_EXECUTABLE}" describe --always --abbrev=7 --dirty
  WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
  OUTPUT_VARIABLE GIT_SHA1
  ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)

execute_process(COMMAND
  "${GIT_EXECUTABLE}" log -1 "--format=%<(40,trunc)%s"
  WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
  OUTPUT_VARIABLE GIT_COMMIT_SUBJECT
  OUTPUT_STRIP_TRAILING_WHITESPACE)

string(TIMESTAMP COMPILE_TIME "%Y.%m.%d %H:%M:%S")

add_custom_target(invalidate_files ALL COMMAND ${CMAKE_COMMAND} -E touch ${CMAKE_CURRENT_SOURCE_DIR}/include/base/cmake_config.hpp.in)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/include/base/cmake_config.hpp.in" "${CMAKE_CURRENT_SOURCE_DIR}/include/base/cmake_config.hpp" @ONLY)

set(DOBBY_DEBUG OFF CACHE INTERNAL "" FORCE)
set(DOBBY_GENERATE_SHARED OFF CACHE INTERNAL "" FORCE)
add_subdirectory(external/Dobby)
target_link_libraries(gdmod dobby)

target_link_libraries(gdmod ${CMAKE_CURRENT_SOURCE_DIR}/external/cocos2d/libcocos2dcpp.so)
target_link_libraries(gdmod ${CMAKE_CURRENT_SOURCE_DIR}/external/fmod/libfmod.so)

