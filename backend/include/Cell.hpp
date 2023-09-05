#pragma once

#include <functional> // std::hash
#include <iostream>

using std::hash;
using std::ostream;
using std::size_t;

class Cell {
private:
    int _row;
    int _col;

public:
    Cell() = default;
    Cell(int row, int col);
    Cell(const Cell& c) = default;
    Cell& operator=(const Cell& m) = default;
    ~Cell() = default;
    Cell(Cell&& cell) = default;
    Cell& operator=(Cell&& cell) = default;

    inline bool operator==(const Cell& c) const
    {
        return (_row == c._row && _col == c._col);
    }

    inline bool operator!=(const Cell& c)
    {
        return !(*this == c);
    }

    friend ostream& operator<<(ostream& os, const Cell& c)
    {
        os << "(" << c._row << "," << c._col << ")" << std::endl;
        return os;
    }

    // Cell is used is adjacency list, which is an unordered map
    // so it needs both operator == and ()
    inline std::size_t operator()(const Cell& c) const
    {
        size_t rowhash = std::hash<int>()(c._row);
        size_t colhash = std::hash<int>()(c._col) << 1;

        return rowhash ^ colhash;
    }

    bool isOnTopSide() const;
    bool isOnRightSide(int mazeWidth) const;
    bool isOnBottomSide(int mazeHeight) const;
    bool isOnLeftSide() const;

    Cell getTopNeighbor() const;
    Cell getRightNeighbor(int mazeWidth) const;
    Cell getBottomNeighbor(int mazeHeight) const;
    Cell getLeftNeighbor() const;

    bool isTopNeighbor(Cell cell) const;
    bool isRightNeighbor(Cell cell, int mazeWidth) const;
    bool isBottomNeighbor(Cell cell, int mazeHeight) const;
    bool isLeftNeighbor(Cell cell) const;

    int getRow() const;
    int getCol() const;
};