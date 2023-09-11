#pragma once

#include "MazeGraph.hpp"
#include <random>

class Maze {
private:
    int _width;
    int _height;

    Cell _entryPos;
    Cell _exitPos;

    MazeGraph _graph;

    bool allAdjacentVisited(int cellIndex, std::unordered_map<int, bool>& visited);
    int chooseRandomAdjacent(vector<int>& adjacents);
    std::vector<int> getAdjacents(int cellIndex, std::unordered_map<int, bool>& visited, bool visitedValue);

    std::default_random_engine _randomEngine;

    int a_star_heuristic(int index);
    int euclidianDistance(int cellA, int cellB);

public:
    Maze() = delete;
    Maze(int width, int height, const Cell& entryPos, const Cell& exitPos);
    Maze(const Maze& m) = default;
    ~Maze() = default;
    Maze(Maze&& facade) = default;
    Maze& operator=(Maze&& maze) = default;
    Maze& operator=(const Maze& m) = default;

    std::vector<CellMetadata> getCellsMetadata();

    void huntAndKill();
    void backtracking();

    bool solveWithAStar();
};