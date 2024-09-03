cmake_minimum_required(VERSION 3.10)
project(StdReport)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "src/*.h")

add_executable(StdReport ${SOURCES} ${HEADERS})
