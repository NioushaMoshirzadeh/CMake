cmake_minimum_required(VERSION 3.10.2)

project(CoordinateGenerator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)



add_subdirectory(Components/InputHandler)
add_subdirectory(Components/Engine)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} InputHandling )
target_link_libraries(${PROJECT_NAME}  MatchingTemplate)

