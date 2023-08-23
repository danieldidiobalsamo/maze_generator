#pragma once

#include <random>
#include <time.h>
#include <tuple>

#include "MazeGraph.hpp"

struct CellWalls {
    bool left;
    bool bottom;
    bool right;
    bool top;
};

class MazeGrid {
private:
    int _width;
    int _height;

    Cell _entryPos;
    Cell _exitPos;

    MazeGraph _graph;

    std::default_random_engine _randomEngine;

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