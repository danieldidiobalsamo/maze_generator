#pragma once

#include <map>
#include <unordered_map>
#include <vector>

#include "Cell.hpp"

using std::map;
using std::unordered_map;
using std::vector;

class MazeGraph {
private:
    int _width;
    int _height;

    unordered_map<Cell, vector<Cell>, Cell> _adjacencyList;

    std::map<int, std::vector<bool>> _visitedMatrix;

    int mazeCoordToIndex(Cell coord);

public:
    MazeGraph() = delete;
    MazeGraph(int w, int h);
    MazeGraph(const MazeGraph& m) = default;
    MazeGraph& operator=(const MazeGraph& m) = default;
    ~MazeGraph();

    void linkCells(Cell src, Cell dest);
    bool wallsBetween(Cell src, Cell dest);
    bool isCellVisited(Cell cell);
    void setVisited(Cell cell);

    vector<Cell> getSurroundingCells(Cell cell);
};