cmake_minimum_required(VERSION 3.5)

project(APP_consola LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(APP_consola main.cpp db_local.cpp db_local.h)
target_link_libraries( APP_consola sqlite3 )
