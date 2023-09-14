#pragma once

#include <iostream>
#include <map>
#include <random>
#include <time.h>
#include <unordered_map>
#include <vector>

#include "Cell.hpp"

using std::map;
using std::ostream;
using std::unordered_map;
using std::vector;

class MazeGraph {
private:
    int _width;
    int _height;

    Cell _entryPos;
    Cell _exitPos;

    unordered_map<int, vector<int>> _adjacencyList;
    vector<Cell> _cells;

    void initCells();
    void carveOutsideMaze(Cell& cell);

    std::default_random_engine _randomEngine;

public:
    MazeGraph() = delete;
    MazeGraph(int w, int h, const Cell& entryPos, const Cell& exitPos);
    MazeGraph(const MazeGraph& m) = delete;
    MazeGraph& operator=(const MazeGraph& m) = delete;
    ~MazeGraph() = default;
    MazeGraph(MazeGraph&& graph) = delete;
    MazeGraph& operator=(MazeGraph&& graph) = delete;

    int getWidth();
    int getHeight();
    Cell getEntry();
    Cell getExit();

    vector<CellMetadata> getCellsMetadata();

    void carve(int srcIndex, int destIndex);

    const unordered_map<int, vector<int>>& getAdjacencyList();

    int mazeCoordToIndex(const Cell& coord);
    int mazeCoordToIndex(int row, int col);
    Cell indexToMazeCoord(int index);

    void addToPath(int cellIndex);

    int chooseRandomAdjacent(std::vector<int>& adjacents);
    std::vector<int> getAdjacents(int cellIndex, const std::vector<bool>& visited, bool visitedValue);

    void setParams(const int w, const int h, const Cell& entryPos, const Cell& exitPos);
};