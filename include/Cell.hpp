#ifndef CELL_HPP
#define CELL_HPP

#include "Walls.hpp"

class Cell {
private:
    int _row;
    int _col;

    bool _visited;
    bool _isEntry;
    bool _isExit;

    Walls _walls;

public:
    Cell();
    Cell(const int row, const int col, const bool built, const bool isEntry, const bool isExit);
    Cell(const Cell& c);
    ~Cell();
    Cell& operator=(const Cell& c);

    void setVisited(const bool visited);
    bool isVisited() const;

    Walls getWalls() const;
    void setWalls(const bool north, const bool west, const bool south, const bool east);
    void setNorthWall(const bool built);
    void setWestWall(const bool built);
    void setSouthWall(const bool built);
    void setEastWall(const bool built);
};

#endif