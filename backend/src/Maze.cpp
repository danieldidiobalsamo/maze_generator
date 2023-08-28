#include "Maze.hpp"

#include <iostream>
#include <stdexcept>

Maze::Maze(int width, int height, Cell entryPos, Cell exitPos)
    : _width(width)
    , _height(height)
    , _entryPos(entryPos)
    , _graph(width, height, entryPos, exitPos)
    , _randomEngine(static_cast<unsigned int>(time(0)))
{
}

Maze::~Maze()
{
}

CellWalls Maze::getCellWalls(Cell coords)
{
    return _graph.getCellWalls(coords);
}

void Maze::huntAndKill()
{
    std::unordered_map<int, std::vector<bool>> visited;
    visited.reserve(_height);

    for (int row = 0; row < _height; ++row) {
        visited[row].reserve(_width);
        visited[row] = std::vector<bool>(_width, false);
    }

    Cell currentCell = _entryPos;

    visited[currentCell.getRow()][currentCell.getCol()] = true;

    Cell nextCell;
    bool allCellsTreated = false;
    bool huntMode = false;

    // looping on the whole maze
    do {

        do // looping until a dead end is reached
        {
            if (isDeadEnd(currentCell, visited)) {
                // launching hunt mode
                huntMode = true;
            } else {
                // choosing an unvisited cell
                do {
                    nextCell = chooseRandomNeighbors(_graph.getSurroundingCells(currentCell));
                } while (visited[nextCell.getRow()][nextCell.getCol()]);

                visited[nextCell.getRow()][nextCell.getCol()] = true;
                _graph.carve(currentCell, nextCell);

                currentCell = nextCell;
            }

        } while (!huntMode);

        // hunt mode
        // consists in searching for an unvisited cell which have at least a visited one
        // and searching row by row

        bool selectedCell = false;
        int row = 0;

        while (row < _height && !selectedCell) {
            int col = 0;

            while (col < _width && !selectedCell) {
                if (visited[row][col]) {
                    // checking if among its neighbors, there is one who is visited

                    auto [visitedNeighbor, chosenNeighbor] = hasVisitedNeighbor(Cell(row, col), visited);

                    if (visitedNeighbor) {
                        currentCell = Cell(row, col);

                        _graph.carve(currentCell, chosenNeighbor);
                        visited[currentCell.getRow()][currentCell.getCol()] = true;
                        selectedCell = true;
                    }
                }
                ++col;
            }

            ++row;
        }

        if (!selectedCell) {
            allCellsTreated = true;
        }

        huntMode = false;
    } while (!allCellsTreated);
}

bool Maze::isDeadEnd(const Cell cell, std::unordered_map<int, std::vector<bool>>& visited)
{
    auto [hasOne, neighbors] = hasVisitedNeighbor(cell, visited);

    return !hasOne;
}

std::tuple<bool, Cell> Maze::hasVisitedNeighbor(const Cell cell, std::unordered_map<int, std::vector<bool>>& visited)
{
    auto neighbors = _graph.getSurroundingCells(cell);
    std::vector<Cell>::iterator visitedNeighbor = std::find_if(neighbors.begin(), neighbors.end(),
        [&visited](const Cell& cell) {
            return !visited[cell.getRow()][cell.getCol()];
        });

    if (visitedNeighbor != neighbors.end()) {
        return std::make_tuple(true, *visitedNeighbor);
    } else {
        return std::make_tuple(false, *visitedNeighbor);
    }
}

Cell Maze::chooseRandomNeighbors(const std::vector<Cell>& neighbors)
{
    std::uniform_int_distribution<int> intDistribution(0, static_cast<int>(neighbors.size() - 1));
    int randomIndex = intDistribution(_randomEngine);

    return neighbors[randomIndex];
}