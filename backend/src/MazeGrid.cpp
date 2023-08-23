#include "MazeGrid.hpp"

#include <algorithm>
#include <iostream>
#include <stdexcept>

MazeGrid::MazeGrid(const int width, const int height, const Cell entryPos, const Cell exitPos)
    : _width(width)
    , _height(height)
    , _entryPos(entryPos)
    , _exitPos(exitPos)
    , _graph(width, height)
    , _randomEngine(static_cast<unsigned int>(time(0))) // used to generate random int, better than rand()
{

    carveToAllNeighbors(_entryPos);
    carveToAllNeighbors(_exitPos);
}

MazeGrid::~MazeGrid()
{
}

void MazeGrid::carve(const Cell src, const Cell dest)
{
    _graph.linkCells(src, dest);
    _graph.linkCells(dest, src);
}

Cell MazeGrid::chooseRandomNeighbors(const Cell currentCell)
{
    auto neighbors = _graph.getSurroundingCells(currentCell);

    std::uniform_int_distribution<int> intDistribution(0, static_cast<int>(neighbors.size() - 1));
    int randomIndex = intDistribution(_randomEngine);

    return neighbors[randomIndex];
}

bool MazeGrid::isDeadEnd(const Cell cell)
{
    auto [hasOne, neighbors] = hasVisitedNeighbor(cell);

    return !hasOne;
}

void MazeGrid::carveToAllNeighbors(const Cell& cellCoord)
{
    auto neighbors = _graph.getSurroundingCells(cellCoord);

    for (auto cell : neighbors) {
        carve(cellCoord, cell);
    }
}

std::tuple<bool, Cell> MazeGrid::hasVisitedNeighbor(const Cell cell)
{
    auto neighbors = _graph.getSurroundingCells(cell);
    std::vector<Cell>::iterator visitedNeighbor = std::find_if(neighbors.begin(), neighbors.end(),
        [=](const Cell& cell) {
            return !_graph.isCellVisited(cell);
        });

    if (visitedNeighbor != neighbors.end()) {
        return std::make_tuple(true, *visitedNeighbor);
    } else {
        return std::make_tuple(false, *visitedNeighbor);
    }
}

void MazeGrid::setVisited(const Cell cell)
{
    _graph.setVisited(cell);
}

CellWalls MazeGrid::getCellWalls(Cell cell)
{
    CellWalls walls = {
        false,
        false,
        false,
        false
    };

    auto surrounding = _graph.getSurroundingCells(cell);

    // checking if cell is on sides
    if (cell != _entryPos && cell != _exitPos) {
        if (cell.isOnTopSide())
            walls.top = true;
        else if (cell.isOnBottomSide(_height))
            walls.bottom = true;

        if (cell.isOnRightSide(_width))
            walls.right = true;
        else if (cell.isOnLeftSide())
            walls.left = true;
    }

    for (auto neighbor : surrounding) {

        if (_graph.wallsBetween(cell, neighbor)) {
            if (cell.isLeftNeighbor(neighbor)) {
                walls.left = true;
                continue;
            }

            if (cell.isBottomNeighbor(neighbor, _height)) {
                walls.bottom = true;
                continue;
            }

            if (cell.isRightNeighbor(neighbor, _width)) {
                walls.right = true;
                continue;
            }

            if (cell.isTopNeighbor(neighbor)) {
                walls.top = true;
                continue;
            }
        }
    }

    return walls;
}

bool MazeGrid::isCellVisited(Cell cell)
{
    return _graph.isCellVisited(cell);
}