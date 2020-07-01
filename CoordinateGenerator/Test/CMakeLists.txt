file(GLOB mytest_source_files *.cpp)

add_executable(CoordinateTest ${mytest_source_files})

target_link_libraries(CoordinateTest gtest_main InputHandling MatchingTemplate OutputHandler stdc++fs)

find_package(OpenCV REQUIRED)

target_link_libraries(CoordinateTest ${OpenCV_LIBS})

add_test(mycmaketest CoordinateTest)