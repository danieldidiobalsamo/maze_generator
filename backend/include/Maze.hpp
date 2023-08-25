#pragma once

#include "MazeGraph.hpp"

class Maze {
private:
    int _width;
    int _height;

    Cell _entryPos;

    MazeGraph _graph;

    bool isDeadEnd(const Cell cell, std::map<int, std::vector<bool>>& visited);
    std::tuple<bool, Cell> hasVisitedNeighbor(const Cell cell, std::map<int, std::vector<bool>>& visited);
    Cell chooseRandomNeighbors(const Cell cell);

    std::default_random_engine _randomEngine;

public:
    Maze() = delete;
    Maze(int width, int height, Cell entryPos, Cell exitPos);
    Maze(const Maze& m) = default;
    ~Maze();

    Maze& operator=(const Maze& m) = default;

    CellWalls getCellWalls(Cell cell);
    void visitCell(Cell cell);

    void huntAndKill();
};