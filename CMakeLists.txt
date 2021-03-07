cmake_minimum_required(VERSION 2.8.4)

project(MazeGenerator)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -g")

set(SOURCE_FILES src/Maze.cpp src/Cell.cpp src/Walls.cpp)
set(TEST_FILES test/MazeTest.cpp test/CellTest.cpp)
find_package(Boost 1.55 REQUIRED COMPONENTS unit_test_framework)

include_directories(headers ${Boost_INCLUDE_DIR})

add_executable(mazeGenerator src/main.cpp ${SOURCE_FILES})

enable_testing()
add_executable(test_exe ${SOURCE_FILES} ${TEST_FILES})
target_link_libraries(test_exe ${Boost_LIBRARIES})
add_test(Test test_exe)