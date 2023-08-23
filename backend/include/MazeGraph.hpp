#pragma once

#include <map>
#include <vector>

#include "Cell.hpp"

class MazeGraph {
private:
    int _width;
    int _height;

    std::map<int, std::vector<bool>> _adjacencyMatrix;
    std::map<int, std::vector<bool>> _visitedMatrix;

    int mazeCoordToIndex(Cell coord);

public:
    MazeGraph() = delete;
    MazeGraph(int w, int h, bool initCellState);
    MazeGraph(const MazeGraph& m) = delete;
    MazeGraph& operator=(const MazeGraph& m) = delete;
    ~MazeGraph();

    void linkCells(Cell src, Cell dest);
    bool wallsBetween(Cell src, Cell dest);
    bool isCellVisited(Cell cell);
    void setVisited(Cell cell);
};