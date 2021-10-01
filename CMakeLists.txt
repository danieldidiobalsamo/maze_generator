cmake_minimum_required(VERSION 3.10)

project(MazeGenerator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-pedantic -Wall -Wextra -Werror -Wconversion -Wsign-conversion -Wold-style-cast -g")

find_package(Boost 1.55 REQUIRED COMPONENTS unit_test_framework REQUIRED)
find_package(Qt5 COMPONENTS Widgets Quick Core REQUIRED)
find_package(Qt5QuickCompiler)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)#finds includes in build directory

set(SOURCE_FILES src/Maze.cpp src/Cell.cpp src/Walls.cpp src/EngineFacade.cpp src/MazeGrid.cpp)
set(TEST_FILES test/MazeGridTest.cpp)


include_directories(include ${Boost_INCLUDE_DIR})

qt5_wrap_cpp(MOC_FILES include/BackEnd.hpp)
qtquick_compiler_add_resources(RESOURCES qml/main.qrc)

add_executable(mazeGenerator src/main.cpp src/BackEnd.cpp ${SOURCE_FILES} ${RESOURCES} ${MOC_FILES})
target_link_libraries(mazeGenerator PUBLIC Qt5::Widgets Qt5::Quick Qt5::Core)

# UNIT TESTS EXECUTABLE
enable_testing()
add_executable(test_exe ${SOURCE_FILES} ${TEST_FILES})
target_link_libraries(test_exe ${Boost_LIBRARIES})
add_test(TestMaze test_exe)