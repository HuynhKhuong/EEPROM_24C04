cmake_minimum_required(VERSION 3.20)
set (CMAKE_CXX_STANDARD 11 CACHE STRING "Set C++ Standard")
set (CMAKE_CXX_COMPILER "C:/msys64/mingw64/bin/g++.exe" CACHE STRING "Set C++ compiler")

project(NetComponent)

add_executable(NetComponent test.cpp)
set (GLOBAL_PROJECT_DIR ${PROJECT_SOURCE_DIR})
set (VARIABLE_DIR_POSTFIX "var/BTLNHOM11")

get_filename_component(PDUComponent ${GLOBAL_PROJECT_DIR}/PDUConfiguration/${VARIABLE_DIR_POSTFIX}/SignalListDefine.hpp DIRECTORY)
get_filename_component(ReceiveKernelLogic ${GLOBAL_PROJECT_DIR}/ComReceive/common/ComReceive.hpp DIRECTORY)

add_subdirectory(${PROJECT_SOURCE_DIR}/PDUConfiguration)
add_subdirectory(${PROJECT_SOURCE_DIR}/E2EProtect)
add_subdirectory(${PROJECT_SOURCE_DIR}/ComReceive/common)
add_subdirectory(${PROJECT_SOURCE_DIR}/ComReceive/${VARIABLE_DIR_POSTFIX})
add_subdirectory(${PROJECT_SOURCE_DIR}/runnable)

target_link_libraries(NetComponent PUBLIC E2EProtectLibrary)
target_link_libraries(NetComponent PUBLIC ComReceiveKernelLibrary)
target_link_libraries(NetComponent PUBLIC NetRunnableLibrary)
