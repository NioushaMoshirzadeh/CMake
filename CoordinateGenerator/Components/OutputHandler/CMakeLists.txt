project(OutputHandler)
find_package(OpenCV REQUIRED)

message(STATUS "OpenCV_LIBS: ${OpenCV_LIBS}")
message(STATUS "OpenCV include: ${OpenCV_INCLUDE_DIRS}")

set(SOURCES
      implementation/OutputHandler.cpp)

add_library(${PROJECT_NAME} 
            SHARED 
            ${SOURCES}        
           )
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

target_include_directories(${PROJECT_NAME} 
                           PUBLIC 
                           interface
                          )

target_include_directories(${PROJECT_NAME} 
                           PUBLIC
                           {OpenCV_INCLUDE_DIRS}
                          )