#include "BackEnd.hpp"

#include <iostream>

BackEnd::BackEnd()
    : _engine(nullptr)
    , _mazeWidth(0)
    , _mazeHeight(0)
    , _randomIntGenerator(static_cast<unsigned int>(time(0)))
{
}

BackEnd::~BackEnd()
{
    delete _engine;
}

void BackEnd::setGenParams(int width, int height, std::string algo)
{
    _mazeWidth = width;
    _mazeHeight = height;
    _algo = algo;
}

void BackEnd::generateMaze()
{
    std::uniform_int_distribution<int> widthDistrib(0, _mazeWidth - 1);

    auto randomEntry = CellCoord { 0, widthDistrib(_randomIntGenerator) };

    auto exit = CellCoord { _mazeHeight - 1, _mazeWidth - 1 };

    _engine = new EngineFacade(_mazeWidth, _mazeHeight, randomEntry, exit, false);
    _engine->generateMaze(_algo);
}

CellWallsStruct BackEnd::getCell(int row, int col)
{
    auto walls = _engine->getMaze().getCellWalls(CellCoord { row, col });
    return CellWallsStruct { walls.west, walls.south, walls.east, walls.north };
}