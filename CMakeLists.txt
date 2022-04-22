cmake_minimum_required(VERSION 3.9.1)
project(CPU_INFO)

set(CMAKE_C_STANDARD 11)


if("${OPTIMIZE}" STREQUAL "Debug")
    set(CMAKE_BUILD_TYPE "Debug")
elseif("${OPTIMIZE}" STREQUAL "Release")
    set(CMAKE_BUILD_TYPE "Release")
else()
    message(SEND_ERROR "Please, choose correct type of build")
endif()

#set(CMAKE_VERBOSE_MAKEFILE ON)


add_library(reader STATIC  lib/reader.c)
add_library(analyzer STATIC  lib/analyzer.c)
add_library(cleaner STATIC  lib/cleaner.c)
add_library(threads STATIC  lib/threads.c)
add_library(pitbull STATIC  lib/pitbull.c)




#uteki
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(run_ut test/main.cpp test/ut_reader.cpp)
target_compile_options(run_ut PUBLIC -lgtest -lgtest_main)
target_link_libraries(run_ut ${GTEST_LIBRARIES}  pthread reader analyzer)

add_executable(release_app main.c)
target_compile_options(release_app PUBLIC -lpthread)
target_link_libraries(release_app reader analyzer cleaner pitbull pthread) 



