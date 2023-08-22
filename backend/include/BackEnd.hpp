#pragma once

#include <emscripten.h>
#include <emscripten/bind.h>
#include <functional>
#include <string>
#include <utility>
#include <vector>

#include "EngineFacade.hpp"

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

class BackEnd {

public:
    BackEnd();
    ~BackEnd();

    void setGenParams(int width, int height, std::string algo);
    void generateMaze();
    CellWallsStruct getCell(int row, int col);

private:
    EngineFacade* _engine;

    int _mazeWidth;
    int _mazeHeight;
    CellCoord _entryPos;
    CellCoord _exitPos;

    std::string _algo;

    std::default_random_engine _randomIntGenerator;
};

EMSCRIPTEN_BINDINGS(BackEnd)
{
    emscripten::class_<BackEnd>("BackEnd")
        .constructor<>()
        .function("setGenParams", std::function<void(BackEnd&, int, int, std::string)>(&BackEnd::setGenParams))
        .function("generateMaze", &BackEnd::generateMaze)
        .function("getCell", std::function<CellWallsStruct(BackEnd&, int, int)>(&BackEnd::getCell));
}