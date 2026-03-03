cmake_minimum_required(VERSION 3.31)
project(quarks_web)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "app/*.cpp"
    "src/*.cpp"
)

add_executable(quarks_web ${SOURCES})

target_include_directories(quarks
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)



