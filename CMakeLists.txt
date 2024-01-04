cmake_minimum_required(VERSION 3.24)
project(WFC)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE my_src source/*.cpp)
add_executable(${PROJECT_NAME} ${my_src})

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics sfml-audio sfml-network)