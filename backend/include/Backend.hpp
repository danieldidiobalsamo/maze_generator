#pragma once

#include <emscripten/bind.h>
#include <functional>
#include <string>

#include "EngineFacade.hpp"

// redefine an equivalent walls struct so that no emscripten dependencies are introduced in inner backend classes (MazeGrid.hpp), but only in Backend class
// and not to make Backend directly depending on inner classes (should only see EngineFacade)
struct CellWallsStruct {
    bool west;
    bool south;
    bool east;
    bool north;
};

EMSCRIPTEN_BINDINGS(CellWallsStruct)
{
    emscripten::value_object<CellWallsStruct>("CellWallsStruct")
        .field("west", &CellWallsStruct::west)
        .field("south", &CellWallsStruct::south)
        .field("east", &CellWallsStruct::east)
        .field("north", &CellWallsStruct::north);
}

class Backend {

public:
    Backend();
    ~Backend();

    void generateMaze(int width, int height, std::string algo);
    CellWallsStruct getCell(int row, int col);

private:
    EngineFacade _engine;
    std::default_random_engine _randomIntGenerator; // must be init only once
};

EMSCRIPTEN_BINDINGS(Backend)
{
    emscripten::class_<Backend>("Backend")
        .constructor<>()
        .function("generateMaze", std::function<void(Backend&, int, int, std::string)>(&Backend::generateMaze))
        .function("getCell", std::function<CellWallsStruct(Backend&, int, int)>(&Backend::getCell));
}