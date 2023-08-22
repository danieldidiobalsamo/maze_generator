#pragma once

class Cell {
private:
    int _row;
    int _col;

public:
    Cell() = default;
    Cell(int row, int col);
    Cell(const Cell& c) = default;
    Cell& operator=(const Cell& m) = default;
    ~Cell();

    inline bool operator==(const Cell& c)
    {
        return (_row == c._row && _col == c._col);
    }

    inline bool operator!=(const Cell& c)
    {
        return !(*this == c);
    }

    bool isOnTopSide() const;
    bool isOnRightSide(int mazeWidth) const;
    bool isOnBottomSide(int mazeHeight) const;
    bool isOnLeftSide() const;

    Cell getTopNeighbor() const;
    Cell getRightNeighbor(int mazeWidth) const;
    Cell getBottomNeighbor(int mazeHeight) const;
    Cell getLeftNeighbor() const;

    int getRow() const;
    int getCol() const;
};