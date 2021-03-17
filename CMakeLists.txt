cmake_minimum_required(VERSION 2.6)

project(MazeGenerator)

set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -g")


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)#finds includes in build directory
set(CMAKE_AUTOUIC_SEARCH_PATHS interfaces)

set(SOURCE_FILES src/Maze.cpp src/Cell.cpp src/Walls.cpp)
set(TEST_FILES test/MazeTest.cpp test/CellTest.cpp)

find_package(Boost 1.55 REQUIRED COMPONENTS unit_test_framework REQUIRED)
find_package(Qt4 4.8.7 REQUIRED QtCore QtGui)

INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

qt4_wrap_cpp(MOC_FILES include/WallGraphicsItem.hpp include/CellGraphicsItem.hpp include/MazeGraphicsItem.hpp include/MainWindow.hpp)

set(UIS interfaces/MainWindow.ui)
qt4_wrap_ui(UIS_HDRS ${UIS})

include_directories(include ${Boost_INCLUDE_DIR})

add_executable(mazeGenerator src/main.cpp src/MazeApplication.cpp src/MainWindow.cpp src/WallGraphicsItem.cpp src/CellGraphicsItem.cpp  src/MazeGraphicsItem.cpp ${SOURCE_FILES} ${UIS_HDRS} ${MOC_FILES})
target_link_libraries(mazeGenerator PUBLIC Qt4::QtCore Qt4::QtGui)

enable_testing()
add_executable(test_exe ${SOURCE_FILES} ${TEST_FILES})
target_link_libraries(test_exe ${Boost_LIBRARIES})
add_test(Test test_exe)