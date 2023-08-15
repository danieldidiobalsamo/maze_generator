#include "BackEnd.hpp"

#include <iostream>

BackEnd::BackEnd() : _engine(nullptr)
    , _mazeWidth(0)
    , _mazeHeight(0)
    , _randomIntGenerator(static_cast<unsigned int>(time(0)))
{
}

BackEnd::~BackEnd()
{
    delete _engine;
}

void BackEnd::setMazeWidth(int width)
{
    _mazeWidth = width;
}

void BackEnd::setMazeHeight(int height)
{
    _mazeHeight = height;
}

void BackEnd::setAlgo(std::string algo)
{
    _algo = algo;
}

void BackEnd::generateMaze()
{
    std::uniform_int_distribution<int> widthDistrib(0, _mazeWidth - 1);

    std::pair<int, int> randomEntry = std::make_pair(0, widthDistrib(_randomIntGenerator));

    auto exit = std::make_pair(_mazeHeight - 1, _mazeWidth - 1);

    _engine = new EngineFacade(_mazeWidth, _mazeHeight, randomEntry, exit, false);
    _engine->generateMaze(_algo);
}

std::vector<bool> BackEnd::getCell(int row, int col)
{
    std::vector<bool> cellWallsList;

    CellWalls walls = _engine->getMaze().getCellWalls(std::make_pair(row, col));
    // note : getMaze only returns a reference

    cellWallsList.push_back(walls.west);
    cellWallsList.push_back(walls.south);
    cellWallsList.push_back(walls.east);
    cellWallsList.push_back(walls.north);

    return cellWallsList;
}