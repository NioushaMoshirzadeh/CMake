cmake_minimum_required(VERSION 3.10.2)

project(CoordinateGenerator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wformat-nonliteral -Wcast-align -Wpointer-arith \
                                        -Wmissing-prototypes  -Wno-unused-parameter  -Wwrite-strings\
                                        -Wnested-externs -Wcast-qual -Wshadow -Wfloat-equal -ansi")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

include(CTest)

add_subdirectory(Components/InputHandler)
add_subdirectory(Components/Engine)
add_subdirectory(Components/OutputHandler)
add_subdirectory(Test)
add_subdirectory(lib/googletest)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}  InputHandling)
target_link_libraries(${PROJECT_NAME}  MatchingTemplate)
target_link_libraries(${PROJECT_NAME}  OutputHandler)
target_link_libraries(${PROJECT_NAME}  stdc++fs)
