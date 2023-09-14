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

int Cell::getRow() const
{
    return _row;
}

int Cell::getCol() const
{
    return _col;
}

CellMetadata Cell::getMetaData()
{
    return _metadata;
}