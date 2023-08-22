#pragma once

#include <map>
#include <random>
#include <time.h>
#include <tuple>
#include <vector>

#include "Cell.hpp"

struct CellWalls {
    bool west;
    bool south;
    bool east;
    bool north;
};

class MazeGrid {
private:
    int _width;
    int _height;

    Cell _entryPos;
    Cell _exitPos;

    std::map<int, std::vector<bool>> _adjacencyMatrix;
    std::map<int, std::vector<bool>> _visitedMatrix;

    std::default_random_engine _randomEngine;

    int mazeCoordToIndex(Cell coord);

public:
    MazeGrid() = delete;
    MazeGrid(const int width, const int height, const Cell entryPos, const Cell exitPos, const bool initCellState);
    MazeGrid(const MazeGrid& m) = delete;

    ~MazeGrid();

    MazeGrid& operator=(const MazeGrid& m) = delete;

    void carve(const Cell src, const Cell dest);
    void carveToAllNeighbors(const Cell& cellCoord);
    Cell chooseRandomNeighbors(const Cell currentCell);
    bool isDeadEnd(const Cell cell);
    std::tuple<bool, Cell> hasVisitedNeighbor(const Cell cell);
    std::vector<Cell> getNeighbors(const Cell cell);
    void setVisited(const Cell cell);
    CellWalls getCellWalls(Cell cell);

    bool isCellVisited(Cell cell);
};