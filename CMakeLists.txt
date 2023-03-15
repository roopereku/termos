cmake_minimum_required(VERSION 3.0)
project(termos)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()

file(GLOB Sources termos/*.cc)
add_library(termos ${Sources})

target_include_directories(termos PUBLIC termos/include)
target_link_libraries(termos ncurses)

if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
	target_compile_definitions(termos PUBLIC -DDEBUG)
endif()

project(termostest)

add_executable(termostest test.cc)
target_link_libraries(termostest termos)
