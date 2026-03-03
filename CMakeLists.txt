cmake_minimum_required(VERSION 3.31)
project(quarks_web)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER "clang++")

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "app/*.cpp"
    "src/*.cpp"
)

add_executable(quarks ${SOURCES})

target_include_directories(quarks
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)



