cmake_minimum_required(VERSION 3.10)

project(MazeGenerator)

# C++ standard and compilation flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-pedantic -Wall -Wextra -Werror -Wconversion -Wold-style-cast -g")

# packages
find_package(Boost 1.55 REQUIRED COMPONENTS unit_test_framework REQUIRED)
find_package(Qt5 COMPONENTS Quick REQUIRED)

# CMake tools
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

#sources
set(SRC
    src/BackEnd.cpp
    src/Maze.cpp
    src/Cell.cpp
    src/Walls.cpp
    src/EngineFacade.cpp
    src/MazeGrid.cpp

    include/BackEnd.hpp
    include/Maze.hpp
    include/Cell.hpp
    include/Walls.hpp
    include/EngineFacade.hpp
    include/MazeGrid.hpp

    qml/main.qrc)

include_directories(include ${Boost_INCLUDE_DIR})

# executable
add_executable(mazeGenerator src/main.cpp ${SRC})
target_link_libraries(mazeGenerator PUBLIC Qt5::Quick)

# unit tests executable

set(TEST_FILES test/MazeGridTest.cpp)

enable_testing()
add_executable(test_exe ${SRC} ${TEST_FILES})
target_link_libraries(test_exe PUBLIC ${Boost_LIBRARIES} Qt5::Quick)
add_test(TestMaze test_exe)