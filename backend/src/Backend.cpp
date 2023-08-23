#include "Backend.hpp"

Backend::Backend()
    : _engine(0, 0, Cell(0, 0), Cell(0, 0), false)
    , _randomIntGenerator(static_cast<unsigned int>(time(0)))
{
}

Backend::~Backend()
{
}

void Backend::generateMaze(int width, int height, std::string algo)
{
    std::uniform_int_distribution<int> widthDistrib(0, width - 1);
    auto randomEntry = Cell(0, widthDistrib(_randomIntGenerator));

    auto exit = Cell(height - 1, width - 1);

    _engine = EngineFacade(width, height, randomEntry, exit, false);
    _engine.generateMaze(algo);
}

CellWallsStruct Backend::getCell(int row, int col)
{
    auto walls = _engine.getMaze().getCellWalls(Cell(row, col));
    // redefine an equivalent walls struct so that no emscripten dependencies are introduced in inner backend classes (MazeGrid.hpp), but only in Backend class
    // and not to make Backend directly depending on inner classes (should only see EngineFacade)
    return CellWallsStruct { walls.left, walls.bottom, walls.right, walls.top };
}