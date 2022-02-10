#include "MazeGrid.hpp"

#include <iostream>
#include <stdexcept>

MazeGrid::MazeGrid(const int width, const int height)
    : _randomEngine(static_cast<unsigned int>(time(0))) // used to generate random int, better than rand()
{
    _width = width;
    _height = height;

    for (int row = 0; row < _height; ++row) 
    {
        for(int col = 0; col < _width; ++col)
        {
            _adjacencyMatrix[row].push_back(false);
            _visitedMatrix[row].push_back(false);
        }
    }
}

MazeGrid::MazeGrid(const int width, const int height, const CellCoord entryPos, const CellCoord exitPos, bool allWallsBuilt)
    : _randomEngine(static_cast<unsigned int>(time(0))) // used to generate random int, better than rand()
{
    _width = width;
    _height = height;

    _entryPos = entryPos;
    _exitPos = exitPos;

    for (int row = 0; row < _height; ++row) 
    {
        for(int col = 0; col < _width; ++col)
        {
            _adjacencyMatrix[row].push_back(allWallsBuilt);
            _visitedMatrix[row].push_back(false);
        }
    }

    carveToAllNeighbors(_entryPos);
    carveToAllNeighbors(_exitPos);
}

MazeGrid::~MazeGrid()
{
}

void MazeGrid::carve(const CellCoord src, const CellCoord dest)
{
    try {
        const int srcRow = src.first;
        const int srcCol = src.second;

        const int destRow = dest.first;
        const int destCol = dest.second;

        const bool carvingHorizontally = (srcCol != destCol);
        const bool carvingVertically = (srcRow != destRow);

        //exception
        if (carvingHorizontally && carvingVertically)
            throw std::invalid_argument("Cells must be connected for carving");

        _adjacencyMatrix[srcRow].at(static_cast<size_t>(destCol)) = true;
        _adjacencyMatrix[destCol].at(static_cast<size_t>(srcRow)) = true;

    }catch (const std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
    }
}

CellCoord MazeGrid::chooseRandomNeighbors(const CellCoord currentCell)
{
    std::uniform_int_distribution<int> intDistribution(1, 4);
    int randomIndex = intDistribution(_randomEngine);
    auto neighbors = getNeighbors(currentCell);

    return neighbors[static_cast<size_t>(randomIndex)];
}

std::vector<CellCoord> MazeGrid::getNeighbors(CellCoord cell)
{
    std::vector<CellCoord> neighbor;

    const int row = cell.first;
    const int col = cell.second;

    if (row - 1 > 0)
        neighbor.push_back(std::make_pair(row - 1, col));
    if (row + 1 < _height)
        neighbor.push_back(std::make_pair(row + 1, col));
    if (col - 1 > 0)
        neighbor.push_back(std::make_pair(row, col - 1));
    if (col + 1 < _width)
        neighbor.push_back(std::make_pair(row, col + 1));

    return neighbor;
}

bool MazeGrid::isDeadEnd(std::pair<int, int> cell)
{
    auto [hasOne, neighbors] = hasVisitedNeighbor(cell);

    return !hasOne;
}

void MazeGrid::carveToAllNeighbors(const CellCoord& cellCoord)
{
    auto neighbors = getNeighbors(cellCoord);

    for(auto cell: neighbors)
        carve(cellCoord, cell);
}

std::tuple<bool, CellCoord> MazeGrid::hasVisitedNeighbor(const CellCoord cell)
{
    auto neighbors = getNeighbors(cell);
    CellCoord visitedNeighbor;
    bool hasOne = false;

    for(auto cell: neighbors)
    {
        if(!_visitedMatrix[cell.first][static_cast<size_t>(cell.second)])
        {
            hasOne = true;
            visitedNeighbor = cell;
            break;
        }
    }

    return std::make_tuple(hasOne, visitedNeighbor);
}

void MazeGrid::setVisited(const CellCoord cell)
{
    _visitedMatrix[cell.first][static_cast<size_t>(cell.second)] = true;
}

Cell MazeGrid::getCell(const int row, const int col)
{
    return _grid[std::make_pair(row, col)];
}

Cell MazeGrid::getCell(const CellCoord cell)
{
    return _grid[cell];
}