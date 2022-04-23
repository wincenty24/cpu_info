cmake_minimum_required(VERSION 3.9.1)
project(CPU_INFO)

set(CMAKE_C_STANDARD 11)


if("${OPTIMIZE}" STREQUAL "Debug")
    set(CMAKE_BUILD_TYPE "Debug")
elseif("${OPTIMIZE}" STREQUAL "Release")
    set(CMAKE_BUILD_TYPE "Release")
else()
    message(SEND_ERROR "Please, choose the type of build")
endif()

#set(CMAKE_VERBOSE_MAKEFILE ON)


add_library(reader STATIC lib/reader.c)
add_library(analyzer STATIC lib/analyzer.c)
add_library(cleaner STATIC lib/cleaner.c)
add_library(threads_lib STATIC lib/threads.c)
add_library(pitbull STATIC lib/pitbull.c)

set(src_lib lib/reader.c lib/analyzer.c lib/cleaner.c lib/threads.c lib/pitbull.c lib/threads.c)

set(req_falg -Wall -Wextra -ffast-math -Wno-return-type)

add_library(libki STATIC ${src_lib})
#uteki
find_package(GTest REQUIRED)
set(ut_flag -lgtest -lgtest_main)

add_executable(ut_analyzer "test/main.cpp" "test/ut_analyzer.cpp")
target_compile_options(ut_analyzer PUBLIC ${ut_flag})
target_link_libraries(ut_analyzer ${GTEST_LIBRARIES} analyzer pthread)

set(ut_files "test/main.cpp" "test/ut_reader.cpp")
add_executable(ut_reader ${ut_files})
target_compile_options(ut_reader PUBLIC ${ut_flag})
target_link_libraries(ut_reader ${GTEST_LIBRARIES} reader cleaner pthread)

add_executable(ut_pitbull "test/main.cpp" "test/ut_pitbull.cpp")
target_compile_options(ut_pitbull PUBLIC ${ut_flag})
target_link_libraries(ut_pitbull ${GTEST_LIBRARIES} pitbull threads_lib pthread)


add_executable(cpu_info_app main.c)
target_compile_options(cpu_info_app PUBLIC -lpthread ${req_falg})
target_link_libraries(cpu_info_app libki pthread) 



