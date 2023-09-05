#pragma once

#include "MazeGraph.hpp"
#include <random>

class Maze {
private:
    int _width;
    int _height;

    Cell _entryPos;

    MazeGraph _graph;

    bool isDeadEnd(const Cell& cell, std::unordered_map<int, std::vector<bool>>& visited);
    std::tuple<bool, Cell> hasVisitedNeighbor(const Cell& cell, std::unordered_map<int, std::vector<bool>>& visited);
    Cell chooseRandomNeighbors(const std::vector<Cell>& neighbors);

    std::default_random_engine _randomEngine;

public:
    Maze() = delete;
    Maze(int width, int height, const Cell& entryPos, const Cell& exitPos);
    Maze(const Maze& m) = default;
    ~Maze();

    Maze& operator=(const Maze& m) = default;

    std::vector<CellWalls> getWallsList();

    void huntAndKill();
};