cmake_minimum_required(VERSION 3.0)
project(termos)

file(GLOB Sources termos/*.cc)
add_library(termos ${Sources})
target_link_libraries(termos ncurses)

project(termostest)

add_executable(termostest test.cc)
target_link_libraries(termostest termos)
