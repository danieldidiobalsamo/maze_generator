#include "MazeGrid.hpp"

#include <algorithm>
#include <iostream>
#include <stdexcept>

MazeGrid::MazeGrid(const int width, const int height, const CellCoord entryPos, const CellCoord exitPos, bool initCellState)
    : _width(width)
    , _height(height)
    , _entryPos(entryPos)
    , _exitPos(exitPos)
    , _randomEngine(static_cast<unsigned int>(time(0))) // used to generate random int, better than rand()
{
    const int nbCell = _width * _height;

    for (int row = 0; row < nbCell; ++row) {
        for (int col = 0; col < nbCell; ++col) {
            _adjacencyMatrix[row].push_back(initCellState);
        }
    }

    for (int row = 0; row < _height; ++row) {
        for (int col = 0; col < _width; ++col) {
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

        // exception
        if (carvingHorizontally && carvingVertically)
            throw std::invalid_argument("Cells must be connected for carving");

        int srcIndex = mazeCoordToIndex(src);
        int destIndex = mazeCoordToIndex(dest);

        _adjacencyMatrix[srcIndex].at(destIndex) = true;
        _adjacencyMatrix[destIndex].at(srcIndex) = true;

    } catch (const std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
    }
}

CellCoord MazeGrid::chooseRandomNeighbors(const CellCoord currentCell)
{
    auto neighbors = getNeighbors(currentCell);

    std::uniform_int_distribution<int> intDistribution(0, static_cast<int>(neighbors.size() - 1));
    int randomIndex = intDistribution(_randomEngine);

    return neighbors[randomIndex];
}

std::vector<CellCoord> MazeGrid::getNeighbors(CellCoord cell)
{
    std::vector<CellCoord> neighbors;

    const int row = cell.first;
    const int col = cell.second;

    if (row - 1 >= 0)
        neighbors.push_back(std::make_pair(row - 1, col));
    if (row + 1 < _height)
        neighbors.push_back(std::make_pair(row + 1, col));
    if (col - 1 >= 0)
        neighbors.push_back(std::make_pair(row, col - 1));
    if (col + 1 < _width)
        neighbors.push_back(std::make_pair(row, col + 1));

    return neighbors;
}

bool MazeGrid::isDeadEnd(std::pair<int, int> cell)
{
    auto [hasOne, neighbors] = hasVisitedNeighbor(cell);

    return !hasOne;
}

void MazeGrid::carveToAllNeighbors(const CellCoord& cellCoord)
{
    auto neighbors = getNeighbors(cellCoord);

    for (auto cell : neighbors) {
        carve(cellCoord, cell);
    }
}

std::tuple<bool, CellCoord> MazeGrid::hasVisitedNeighbor(const CellCoord cell)
{
    auto neighbors = getNeighbors(cell);
    std::vector<CellCoord>::iterator visitedNeighbor = std::find_if(neighbors.begin(), neighbors.end(),
        [=](const CellCoord& cell) {
            return !_visitedMatrix[cell.first][cell.second];
        });

    if (visitedNeighbor != neighbors.end()) {
        return std::make_tuple(true, *visitedNeighbor);
    } else {
        return std::make_tuple(false, *visitedNeighbor);
    }
}

void MazeGrid::setVisited(const CellCoord cell)
{
    _visitedMatrix[cell.first][cell.second] = true;
}

CellWalls MazeGrid::getCellWalls(CellCoord cell)
{
    const int row = cell.first;
    const int col = cell.second;

    CellWalls walls = {
        false,
        false,
        false,
        false
    };

    auto neighbors = getNeighbors(cell);
    int cellIndex = mazeCoordToIndex(cell);

    // drawing borders
    if (cell != _entryPos && cell != _exitPos) {
        // drawing nothern, border
        if (cell.first == 0)
            walls.north = true;

        // drawing southern, border
        if (cell.first == _height - 1)
            walls.south = true;

        // drawing eastern, border
        if (cell.second == _width - 1)
            walls.east = true;

        // drawing nothern, border
        if (cell.second == 0)
            walls.west = true;
    }

    for (auto neighbor : neighbors) {
        int neighborRow = neighbor.first;
        int neighborCol = neighbor.second;

        if (neighbor.second == col - 1) {
            int neighborIndex = mazeCoordToIndex(std::make_pair(neighborRow, col - 1));

            if (!_adjacencyMatrix[cellIndex][neighborIndex]) {
                walls.west = true;
                continue;
            }
        }

        if (neighbor.first == row + 1) {
            int neighborIndex = mazeCoordToIndex(std::make_pair(row + 1, neighborCol));
            if (!_adjacencyMatrix[cellIndex][neighborIndex]) {
                walls.south = true;
                continue;
            }
        }

        if (neighbor.second == col + 1) {
            int neighborIndex = mazeCoordToIndex(std::make_pair(neighborRow, col + 1));
            if (!_adjacencyMatrix[cellIndex][neighborIndex]) {
                walls.east = true;
                continue;
            }
        }

        if (neighbor.first == row - 1) {
            int neighborIndex = mazeCoordToIndex(std::make_pair(row - 1, neighborCol));
            if (!_adjacencyMatrix[cellIndex][neighborIndex]) {
                walls.north = true;
                continue;
            }
        }
    }

    return walls;
}

bool MazeGrid::isCellVisited(CellCoord cell)
{
    return _visitedMatrix[cell.first][cell.second];
}

int MazeGrid::mazeCoordToIndex(CellCoord coord)
{
    return (_width * coord.first) + coord.second;
}