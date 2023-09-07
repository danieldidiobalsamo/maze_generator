#include "Cell.hpp"

Cell::Cell(int row, int col)
    : _row(row)
    , _col(col)
    , _metadata()
{
}

Cell::Cell(int row, int col, CellMetadata metadata)
    : _row(row)
    , _col(col)
    , _metadata(metadata)
{
}

bool Cell::isOnTopSide() const
{
    return _row == 0;
}

bool Cell::isOnRightSide(int mazeWidth) const
{
    return _col == mazeWidth - 1;
}

bool Cell::isOnBottomSide(int mazeHeight) const
{
    return _row == mazeHeight - 1;
}

bool Cell::isOnLeftSide() const
{
    return _col == 0;
}

Cell Cell::getLeftNeighbor() const
{
    if (_col - 1 >= 0)
        return Cell(_row, _col - 1);
    else
        return *this;
}

Cell Cell::getBottomNeighbor(int mazeHeight) const
{
    if (_row + 1 < mazeHeight)
        return Cell(_row + 1, _col);
    else
        return *this;
}

Cell Cell::getTopNeighbor() const
{
    if (_row - 1 >= 0)
        return Cell(_row - 1, _col);
    else
        return *this;
}

Cell Cell::getRightNeighbor(int mazeWidth) const
{
    if (_col + 1 < mazeWidth)
        return Cell(_row, _col + 1);
    else
        return *this;
}

int Cell::getRow() const
{
    return _row;
}

int Cell::getCol() const
{
    return _col;
}

bool Cell::isTopNeighbor(const Cell& cell) const
{
    return (cell.getRow() == getRow() - 1) && (getRow() - 1 >= 0);
}
bool Cell::isRightNeighbor(const Cell& cell, int mazeWidth) const
{
    return (cell.getCol() == getCol() + 1) && (getCol() + 1 < mazeWidth);
}
bool Cell::isBottomNeighbor(const Cell& cell, int mazeHeight) const
{
    return (cell.getRow() == getRow() + 1) && (getRow() + 1 < mazeHeight);
}
bool Cell::isLeftNeighbor(const Cell& cell) const
{
    return (cell.getCol() == getCol() - 1) && (getCol() - 1 >= 0);
}

CellMetadata Cell::getMetaData()
{
    return _metadata;
}