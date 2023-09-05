#pragma once

#include <iostream>
#include <map>
#include <unordered_map>

#include "Cell.hpp"

using std::map;
using std::ostream;
using std::unordered_map;
using std::vector;

struct CellWalls {
    bool left;
    bool bottom;
    bool right;
    bool top;

    inline bool operator==(const CellWalls& c) const
    {
        return (left == c.left && bottom == c.bottom && right == c.right && top == c.top);
    }

    friend ostream& operator<<(ostream& os, const CellWalls& c)
    {
        os << "left: " << c.left << " bottom: " << c.bottom << " right: " << c.right << " top: " << c.top << std::endl;
        return os;
    }
};

class MazeGraph {
private:
    int _width;
    int _height;

    Cell _entryPos;
    Cell _exitPos;

    unordered_map<Cell, vector<Cell>, Cell> _adjacencyList;
    vector<CellWalls> _wallsList;

    int mazeCoordToIndex(const Cell& coord);

public:
    MazeGraph() = delete;
    MazeGraph(int w, int h, const Cell& entryPos, const Cell& exitPos);
    MazeGraph(const MazeGraph& m) = default;
    MazeGraph& operator=(const MazeGraph& m) = default;
    ~MazeGraph() = default;
    MazeGraph(MazeGraph&& graph) = default;
    MazeGraph& operator=(MazeGraph&& graph) = default;

    vector<CellWalls> getWallsList();

    vector<Cell> getSurroundingCells(const Cell& cell);
    void carve(const Cell& src, const Cell& dest);
    void carveToAllNeighbors(const Cell& cell);
};