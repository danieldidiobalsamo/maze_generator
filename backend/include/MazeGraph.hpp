#pragma once

#include <iostream>
#include <map>
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

    void carveOutsideMaze(Cell& cell);

public:
    MazeGraph() = delete;
    MazeGraph(int w, int h, const Cell& entryPos, const Cell& exitPos);
    MazeGraph(const MazeGraph& m) = default;
    MazeGraph& operator=(const MazeGraph& m) = default;
    ~MazeGraph() = default;
    MazeGraph(MazeGraph&& graph) = default;
    MazeGraph& operator=(MazeGraph&& graph) = default;

    vector<CellMetadata> getCellsMetadata();

    void carve(int srcIndex, int destIndex);

    const unordered_map<int, vector<int>>& getAdjacencyList();

    int mazeCoordToIndex(const Cell& coord);
    int mazeCoordToIndex(int row, int col);
    Cell indexToMazeCoord(int index);

    void addToPath(int cellIndex);
};