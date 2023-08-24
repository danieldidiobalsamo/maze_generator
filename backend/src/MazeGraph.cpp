#include "MazeGraph.hpp"

#include <algorithm>
#include <iostream>
#include <stdexcept>

MazeGraph::MazeGraph(int w, int h, Cell entryPos, Cell exitPos)
    : _width(w)
    , _height(h)
    , _entryPos(entryPos)
    , _exitPos(exitPos)
    , _adjacencyList()
    , _randomEngine(static_cast<unsigned int>(time(0))) // used to generate random int, better than rand()
{
    for (int row = 0; row < _height; ++row) {
        for (int col = 0; col < _width; ++col) {
            _visitedMatrix[row].push_back(false);
        }
    }

    carveToAllNeighbors(_entryPos);
    carveToAllNeighbors(_exitPos);
}

MazeGraph::~MazeGraph()
{
}

void MazeGraph::linkCells(Cell src, Cell dest)
{
    try {
        const bool carvingHorizontally = (src.getCol() != dest.getCol());
        const bool carvingVertically = (src.getRow() != dest.getRow());

        // exception
        if (carvingHorizontally && carvingVertically)
            throw std::invalid_argument("Cells must be connected for carving");

        _adjacencyList[src].push_back(dest);
        _adjacencyList[dest].push_back(src);

    } catch (const std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
    }
}

bool MazeGraph::wallsBetween(Cell src, Cell dest)
{
    std::vector<Cell>::iterator cell = std::find_if(_adjacencyList[src].begin(), _adjacencyList[src].end(),
        [=](const Cell& cell) {
            return cell == dest;
        });

    return cell == _adjacencyList[src].end();
}

bool MazeGraph::isCellVisited(Cell cell)
{
    return _visitedMatrix[cell.getRow()][cell.getCol()];
}

void MazeGraph::setVisited(Cell cell)
{
    _visitedMatrix[cell.getRow()][cell.getCol()] = true;
}

vector<Cell> MazeGraph::getSurroundingCells(Cell cell)
{
    std::vector<Cell> surrouding; // not necessary neighbors, just cells around

    if (cell.getRow() - 1 >= 0)
        surrouding.push_back(cell.getTopNeighbor());
    if (cell.getRow() + 1 < _height)
        surrouding.push_back(cell.getBottomNeighbor(_height));
    if (cell.getCol() - 1 >= 0)
        surrouding.push_back(cell.getLeftNeighbor());
    if (cell.getCol() + 1 < _width)
        surrouding.push_back(cell.getRightNeighbor(_width));

    return surrouding;
}

void MazeGraph::carve(const Cell src, const Cell dest)
{
    linkCells(src, dest);
    linkCells(dest, src);
}

void MazeGraph::carveToAllNeighbors(const Cell cell)
{
    auto neighbors = getSurroundingCells(cell);

    for (auto neighbor : neighbors) {
        carve(cell, neighbor);
    }
}

Cell MazeGraph::chooseRandomNeighbors(const Cell cell)
{
    auto neighbors = getSurroundingCells(cell);

    std::uniform_int_distribution<int> intDistribution(0, static_cast<int>(neighbors.size() - 1));
    int randomIndex = intDistribution(_randomEngine);

    return neighbors[randomIndex];
}

bool MazeGraph::isDeadEnd(const Cell cell)
{
    auto [hasOne, neighbors] = hasVisitedNeighbor(cell);

    return !hasOne;
}

std::tuple<bool, Cell> MazeGraph::hasVisitedNeighbor(const Cell cell)
{
    auto neighbors = getSurroundingCells(cell);
    std::vector<Cell>::iterator visitedNeighbor = std::find_if(neighbors.begin(), neighbors.end(),
        [this](const Cell& cell) {
            return !isCellVisited(cell);
        });

    if (visitedNeighbor != neighbors.end()) {
        return std::make_tuple(true, *visitedNeighbor);
    } else {
        return std::make_tuple(false, *visitedNeighbor);
    }
}

CellWalls MazeGraph::getCellWalls(Cell cell)
{
    CellWalls walls = {
        false,
        false,
        false,
        false
    };

    auto surrounding = getSurroundingCells(cell);

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

        if (wallsBetween(cell, neighbor)) {
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