#include "Cell.hpp"

Cell::Cell(int row, int col)
    : _row(row)
    , _col(col)
{
}

Cell::~Cell()
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