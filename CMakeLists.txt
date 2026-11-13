cmake_minimum_required(VERSION 3.20)

project(linux_monitor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(linux_monitor
    src/main.cpp
    src/cpu_collector.cpp
    src/mem_collector.cpp
)

target_include_directories(linux_monitor PRIVATE include)
