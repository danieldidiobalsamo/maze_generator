cmake_minimum_required(VERSION 3.10)

project(MazeGenerator)

# C++ standard and compilation flags
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-pedantic -Wall -Wextra -Werror -Wold-style-cast -Wno-unused-command-line-argument")

option(EMCC "Compile with emcc" OFF)

set(SRC
    src/Maze.cpp
    src/EngineFacade.cpp
    src/Cell.cpp
    src/MazeGraph.cpp

    include/Maze.hpp
    include/EngineFacade.hpp
    include/Cell.hpp
    include/MazeGraph.hpp)

IF(${EMCC})
    set(CMAKE_CXX_COMPILER emcc) # emscripten compiler
    set(CMAKE_EXECUTABLE_SUFFIX ".js")

    set(EMCC_FLAGS "-sEXPORTED_RUNTIME_METHODS=['ccall'] -sEXPORT_ES6=1 -sMODULARIZE=1 -o MazeGenerator.js -sEXPORT_NAME='MazeGenerator' --bind ")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${EMCC_FLAGS}")
    set(SRC ${SRC} src/Backend.cpp include/Backend.hpp)
ELSE()
    find_package(Boost 1.55 REQUIRED COMPONENTS unit_test_framework REQUIRED)
ENDIF()

include_directories(include ${Boost_INCLUDE_DIR})

# executable
add_executable(mazeGenerator src/main.cpp ${SRC})
set_target_properties(mazeGenerator PROPERTIES LINK_FLAGS "-o mazeGenerator.html")


IF(NOT ${CMAKE_CXX_COMPILER} MATCHES "emcc")
    # unit tests executable
    set(TEST_FILES test/MazeGraphTest.cpp)

    enable_testing()
    add_executable(test_exe ${SRC} ${TEST_FILES})
    target_link_libraries(test_exe PUBLIC ${Boost_LIBRARIES})
    add_test(TestMaze test_exe)
ENDIF()