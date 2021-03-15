cmake_minimum_required(VERSION 3.17)
project(clipboard C)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED gtk+-3.0)

include_directories(${GTK_INCLUDE_DIRS})
link_directories(${GTK_LIBRARY_DIRS})

add_definitions(${GTK_FLAGS_OTHER})

set(CMAKE_C_STANDARD 11)

add_executable(clipboard main.c linked_list.c linked_list.h)
target_link_libraries(clipboard ${GTK_LIBRARIES})