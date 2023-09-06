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

struct CellWalls {
    bool left;
    bool bottom;
    bool right;
    bool top;

    inline bool operator==(const CellWalls& w) const
    {
        return (w.left == left && w.bottom == bottom && w.right == right && w.top == top);
    }

    friend ostream& operator<<(ostream& os, const CellWalls& w)
    {
        os << "left: " << w.left << " bottom: " << w.bottom << " right: " << w.right << " top: " << w.top << std::endl;
        return os;
    }
};

struct CellMetadata {

    CellWalls walls;
    bool isPath;

    inline bool operator==(const CellMetadata& c) const
    {
        return (c.walls == walls && c.isPath == isPath);
    }

    friend ostream& operator<<(ostream& os, const CellMetadata& c)
    {
        os << c.walls << "belongs to path: " << c.isPath << std::endl;
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
    vector<CellMetadata> _cellsMetadata;

    int mazeCoordToIndex(const Cell& coord);

public:
    MazeGraph() = delete;
    MazeGraph(int w, int h, const Cell& entryPos, const Cell& exitPos);
    MazeGraph(const MazeGraph& m) = default;
    MazeGraph& operator=(const MazeGraph& m) = default;
    ~MazeGraph() = default;
    MazeGraph(MazeGraph&& graph) = default;
    MazeGraph& operator=(MazeGraph&& graph) = default;

    vector<CellMetadata> getCellsMetadata();

    vector<Cell> getSurroundingCells(const Cell& cell);
    void carve(const Cell& src, const Cell& dest);
    void carveToAllNeighbors(const Cell& cell);
};