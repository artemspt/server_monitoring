cmake_minimum_required(VERSION 3.16)
project(server_monitoring VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(BUILD_TESTS "Build tests" OFF)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME} src/main.cpp
        src/agent/cpu_load_reader.cpp
        src/agent/cpu_load_reader.h
        src/agent/memory_load_reader.cpp
        src/agent/memory_load_reader.h
        src/agent/cpu_temp_reader.cpp
        src/agent/cpu_temp_reader.h
        src/agent/get_pc_passport.cpp
        src/agent/get_pc_passport.h)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()