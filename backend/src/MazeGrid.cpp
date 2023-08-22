#include "MazeGrid.hpp"

#include <algorithm>
#include <iostream>
#include <stdexcept>

MazeGrid::MazeGrid(const int width, const int height, const Cell entryPos, const Cell exitPos, bool initCellState)
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

void MazeGrid::carve(const Cell src, const Cell dest)
{
    try {
        const bool carvingHorizontally = (src.getCol() != dest.getCol());
        const bool carvingVertically = (src.getRow() != dest.getRow());

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
            return !_visitedMatrix[cell.getRow()][cell.getCol()];
        });

    if (visitedNeighbor != neighbors.end()) {
        return std::make_tuple(true, *visitedNeighbor);
    } else {
        return std::make_tuple(false, *visitedNeighbor);
    }
}

void MazeGrid::setVisited(const Cell cell)
{
    _visitedMatrix[cell.getRow()][cell.getCol()] = true;
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
    int cellIndex = mazeCoordToIndex(cell);

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
        if (neighbor.getCol() == cell.getCol() - 1) {
            const int neighborIndex = mazeCoordToIndex(cell.getLeftNeighbor());
            if (!_adjacencyMatrix[cellIndex][neighborIndex]) {
                walls.west = true;
                continue;
            }
        }

        if (neighbor.getRow() == cell.getRow() + 1) {
            const int neighborIndex = mazeCoordToIndex(cell.getBottomNeighbor(_height));
            if (!_adjacencyMatrix[cellIndex][neighborIndex]) {
                walls.south = true;
                continue;
            }
        }

        if (neighbor.getCol() == cell.getCol() + 1) {
            const int neighborIndex = mazeCoordToIndex(cell.getRightNeighbor(_width));
            if (!_adjacencyMatrix[cellIndex][neighborIndex]) {
                walls.east = true;
                continue;
            }
        }

        if (neighbor.getRow() == cell.getRow() - 1) {
            const int neighborIndex = mazeCoordToIndex(cell.getTopNeighbor());
            if (!_adjacencyMatrix[cellIndex][neighborIndex]) {
                walls.north = true;
                continue;
            }
        }
    }

    return walls;
}

bool MazeGrid::isCellVisited(Cell cell)
{
    return _visitedMatrix[cell.getRow()][cell.getCol()];
}

int MazeGrid::mazeCoordToIndex(Cell coord)
{
    return (_width * coord.getRow()) + coord.getCol();
}
