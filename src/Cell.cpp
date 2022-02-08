#include "Cell.hpp"

////////////////////////////
// Coplien

Cell::Cell()
    : _row(0)
    , _col(0)
    , _visited(false)
    , _isEntry(false)
    , _isExit(false)
    , _walls()
{
}

Cell::Cell(const int row, const int col, const bool built, const bool isEntry, const bool isExit)
    : _row(row)
    , _col(col)
    , _visited(false)
    , _isEntry(isEntry)
    , _isExit(isExit)
    , _walls(built)
{
}

Cell::Cell(const Cell& c)
{
    _row = c._row;
    _col = c._col;

    _visited = c._visited;
    _isEntry = c._isEntry;
    _isExit = c._isExit;
    _walls = c._walls;
}

Cell::~Cell()
{
}

Cell& Cell::operator=(const Cell& c)
{
    if (this == &c) {
        return *this;
        // (to avoid memory leaks)
    } else {
        _row = c._row;
        _col = c._col;
        _visited = c._visited;
        _isEntry = c._isEntry;
        _isExit = c._isExit;
        _walls = c._walls;

        return *this;
    }
}

Walls Cell::getWalls() const
{
    return _walls;
}

void Cell::setWalls(const bool north, const bool west, const bool south, const bool east)
{
    _walls.setNorthWall(north);
    _walls.setWestWall(west);
    _walls.setSouthWall(south);
    _walls.setEastWall(east);
}

void Cell::setNorthWall(const bool built)
{
    _walls.setNorthWall(built);
}
void Cell::setWestWall(const bool built)
{
    _walls.setWestWall(built);
}
void Cell::setSouthWall(const bool built)
{
    _walls.setSouthWall(built);
}
void Cell::setEastWall(const bool built)
{
    _walls.setEastWall(built);
}

void Cell::setVisited(const bool visited)
{
    _visited = visited;
}

bool Cell::isVisited() const
{
    return _visited;
}

////////////////////////////