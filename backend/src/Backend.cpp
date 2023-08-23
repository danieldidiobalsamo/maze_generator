#include "Backend.hpp"

#include <iostream>

Backend::Backend()
    : _engine(0, 0, Cell(0, 0), Cell(0, 0), false)
    , _mazeWidth(0)
    , _mazeHeight(0)
    , _randomIntGenerator(static_cast<unsigned int>(time(0)))
{
}

Backend::~Backend()
{
}

void Backend::setGenParams(int width, int height, std::string algo)
{
    _mazeWidth = width;
    _mazeHeight = height;
    _algo = algo;

    std::uniform_int_distribution<int> widthDistrib(0, _mazeWidth - 1);
    auto randomEntry = Cell(0, widthDistrib(_randomIntGenerator));

    auto exit = Cell(_mazeHeight - 1, _mazeWidth - 1);

    _engine = EngineFacade(_mazeWidth, _mazeHeight, randomEntry, exit, false);
}

void Backend::generateMaze()
{
    _engine.generateMaze(_algo);
}

CellWallsStruct Backend::getCell(int row, int col)
{
    auto walls = _engine.getMaze().getCellWalls(Cell(row, col));
    // redefine an equivalent walls struct so that no emscripten dependencies are introduced in inner backend classes (MazeGrid.hpp), but only in Backend class
    // and not to make Backend directly depending on inner classes (should only see EngineFacade)
    return CellWallsStruct { walls.left, walls.bottom, walls.right, walls.top };
}