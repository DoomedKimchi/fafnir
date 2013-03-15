# Instructions:
# http://firstforge.wpi.edu/sf/wiki/do/viewPage/projects.c--11_toochain/wiki/UsingCMake

cmake_minimum_required(VERSION 2.8)
 include(FRCDeploy)
 
 project(Robot)
 find_package(WPILib)
 include_directories(${WPILib_INCLUDE_DIR})
 
 file(GLOB_RECURSE SOURCE_CODE *.cpp)
 
 add_executable(Robot ${SOURCE_CODE})
 target_link_libraries(Robot ${WPILib_LIBRARY})
 
 add_make_deploy(Robot 10.00.08.2) # where your team number is xxyy

