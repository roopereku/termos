cmake_minimum_required(VERSION 3.0)
project(termos)

if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
	add_definitions(-DDEBUG)
endif()

file(GLOB_RECURSE Sources termos/*.cc)
add_library(termos ${Sources})
target_link_libraries(termos ncurses)

project(termostest)

add_executable(termostest test.cc)
target_link_libraries(termostest termos)
