#include "MazeGrid.hpp"

#include <algorithm>
#include <iostream>
#include <stdexcept>

MazeGrid::MazeGrid(const int width, const int height, const Cell entryPos, const Cell exitPos, bool initCellState)
    : _width(width)
    , _height(height)
    , _entryPos(entryPos)
    , _exitPos(exitPos)
    , _graph(width, height, initCellState)
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
    auto neighbors = getNeighbors(currentCell);

    std::uniform_int_distribution<int> intDistribution(0, static_cast<int>(neighbors.size() - 1));
    int randomIndex = intDistribution(_randomEngine);

    return neighbors[randomIndex];
}

std::vector<Cell> MazeGrid::getNeighbors(Cell cell)
{
    std::vector<Cell> neighbors;

    if (cell.getRow() - 1 >= 0)
        neighbors.push_back(cell.getTopNeighbor());
    if (cell.getRow() + 1 < _height)
        neighbors.push_back(cell.getBottomNeighbor(_height));
    if (cell.getCol() - 1 >= 0)
        neighbors.push_back(cell.getLeftNeighbor());
    if (cell.getCol() + 1 < _width)
        neighbors.push_back(cell.getRightNeighbor(_width));

    return neighbors;
}

bool MazeGrid::isDeadEnd(const Cell cell)
{
    auto [hasOne, neighbors] = hasVisitedNeighbor(cell);

    return !hasOne;
}

void MazeGrid::carveToAllNeighbors(const Cell& cellCoord)
{
    auto neighbors = getNeighbors(cellCoord);

    for (auto cell : neighbors) {
        carve(cellCoord, cell);
    }
}

std::tuple<bool, Cell> MazeGrid::hasVisitedNeighbor(const Cell cell)
{
    auto neighbors = getNeighbors(cell);
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

    auto neighbors = getNeighbors(cell);

    // checking if cell is on sides
    if (cell != _entryPos && cell != _exitPos) {
        if (cell.isOnTopSide())
            walls.north = true;
        else if (cell.isOnBottomSide(_height))
            walls.south = true;

        if (cell.isOnRightSide(_width))
            walls.east = true;
        else if (cell.isOnLeftSide())
            walls.west = true;
    }

    for (auto neighbor : neighbors) {
        if (cell.isLeftNeighbor(neighbor)) {
            if (!_graph.areCellsLinked(cell, neighbor)) {
                walls.west = true;
                continue;
            }
        }

        if (cell.isBottomNeighbor(neighbor, _height)) {
            if (!_graph.areCellsLinked(cell, neighbor)) {
                walls.south = true;
                continue;
            }
        }

        if (cell.isRightNeighbor(neighbor, _width)) {
            if (!_graph.areCellsLinked(cell, neighbor)) {
                walls.east = true;
                continue;
            }
        }

        if (cell.isTopNeighbor(neighbor)) {
            if (!_graph.areCellsLinked(cell, neighbor)) {
                walls.north = true;
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