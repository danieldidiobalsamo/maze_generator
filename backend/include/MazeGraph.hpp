#pragma once

#include <map>
#include <random>
#include <time.h>
#include <tuple>
#include <unordered_map>
#include <vector>

#include "Cell.hpp"

using std::map;
using std::unordered_map;
using std::vector;

struct CellWalls {
    bool left;
    bool bottom;
    bool right;
    bool top;
};

class MazeGraph {
private:
    int _width;
    int _height;

    Cell _entryPos;
    Cell _exitPos;

    unordered_map<Cell, vector<Cell>, Cell> _adjacencyList;

    void linkCells(Cell src, Cell dest);

public:
    MazeGraph() = delete;
    MazeGraph(int w, int h, Cell entryPos, Cell exitPos);
    MazeGraph(const MazeGraph& m) = default;
    MazeGraph& operator=(const MazeGraph& m) = default;
    ~MazeGraph();

    CellWalls getCellWalls(Cell cell);
    bool wallsBetween(Cell src, Cell dest);

    vector<Cell> getSurroundingCells(Cell cell);
    void carve(const Cell src, const Cell dest);
    void carveToAllNeighbors(const Cell cell);
};