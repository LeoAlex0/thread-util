cmake_minimum_required(VERSION 3.10)
project(thread)

set(CMAKE_CXX_STANDARD 17)
set(LIBRARY_OUTPUT_PATH lib)
set(EXECUTABLE_OUTPUT_PATH bin)

include_directories(include)

link_libraries(pthread)

add_subdirectory(src)
add_subdirectory(tester)