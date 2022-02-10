#include "BackEnd.hpp"

#include <iostream>

BackEnd::BackEnd(QObject* parent)
    : QObject(parent)
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

void BackEnd::setAlgo(QString algo)
{
    _algo = algo;
}

void BackEnd::generateMaze()
{
    std::uniform_int_distribution<int> widthDistrib(0, _mazeWidth - 1);

    std::pair<int, int> randomEntry = std::make_pair(0, widthDistrib(_randomIntGenerator));

    auto exit = std::make_pair(_mazeHeight - 1, _mazeWidth - 1);

    _engine = new EngineFacade(_mazeWidth, _mazeHeight, randomEntry, exit, false);
    _engine->generateMaze(_algo.toStdString());
}

QVariantList BackEnd::getCell(int row, int col)
{
    QVariantList cellWallsList;

    CellWalls walls = _engine->getMaze().getCellWalls(std::make_pair(row, col));
    // note : getMaze only returns a reference

    cellWallsList.append(walls.west);
    cellWallsList.append(walls.south);
    cellWallsList.append(walls.east);
    cellWallsList.append(walls.north);

    return cellWallsList;
}