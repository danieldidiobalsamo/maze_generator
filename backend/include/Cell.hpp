#pragma once

#include <functional> // std::hash
#include <iostream>

using std::hash;
using std::ostream;
using std::size_t;

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

class Cell {

    friend class MazeGraph;

private:
    int _row;
    int _col;

    CellMetadata _metadata;

public:
    Cell() = default;
    Cell(int row, int col);
    Cell(int row, int col, CellMetadata metadata);
    Cell(const Cell& c) = default;
    Cell& operator=(const Cell& m) = default;
    ~Cell() = default;
    Cell(Cell&& cell) = default;
    Cell& operator=(Cell&& cell) = default;

    int getRow() const;
    int getCol() const;

    CellMetadata getMetaData();

    friend ostream& operator<<(ostream& os, const Cell& c)
    {
        os << "(" << c._row << "," << c._col << ") : " << c._metadata << std::endl;
        return os;
    }
};