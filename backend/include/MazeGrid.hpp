#pragma once

#include <map>
#include <random>
#include <time.h>
#include <tuple>
#include <vector>

struct CellCoord {
    int row;
    int col;

    inline bool operator==(const CellCoord& c)
    {
        return (row == c.row && col == c.col);
    }

    inline bool operator!=(const CellCoord& c)
    {
        return !(*this == c);
    }
};

struct CellWalls {
    bool west;
    bool south;
    bool east;
    bool north;
};

class MazeGrid {
private:
    int _width;
    int _height;

    CellCoord _entryPos;
    CellCoord _exitPos;

    std::map<int, std::vector<bool>> _adjacencyMatrix;
    std::map<int, std::vector<bool>> _visitedMatrix;

    std::default_random_engine _randomEngine;

    int mazeCoordToIndex(CellCoord coord);

    bool isCellOnTopSide(CellCoord cell);
    bool isCellOnRightSide(CellCoord cell);
    bool isCellOnBottomSide(CellCoord cell);
    bool isCellOnLeftSide(CellCoord cell);

    CellCoord getTopNeighbor(CellCoord cell);
    CellCoord getRightNeighbor(CellCoord cell);
    CellCoord getBottomNeighbor(CellCoord cell);
    CellCoord getLeftNeighbor(CellCoord cell);

public:
    MazeGrid() = delete;
    MazeGrid(const int width, const int height, const CellCoord entryPos, const CellCoord exitPos, const bool initCellState);
    MazeGrid(const MazeGrid& m) = delete;

    ~MazeGrid();

    MazeGrid& operator=(const MazeGrid& m) = delete;

    void carve(const CellCoord src, const CellCoord dest);
    void carveToAllNeighbors(const CellCoord& cellCoord);
    CellCoord chooseRandomNeighbors(const CellCoord currentCell);
    bool isDeadEnd(const CellCoord cell);
    std::tuple<bool, CellCoord> hasVisitedNeighbor(const CellCoord cell);
    std::vector<CellCoord> getNeighbors(const CellCoord cell);
    void setVisited(const CellCoord cell);
    CellWalls getCellWalls(CellCoord cell);

    bool isCellVisited(CellCoord cell);
};