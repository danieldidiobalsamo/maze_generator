#ifndef MAZE_GRID_HPP
#define MAZE_GRID_HPP

#include "Cell.hpp"

#include <map>
#include <random>
#include <time.h>
#include <tuple>
#include <utility> // pair
#include <vector>

typedef std::pair<int, int> CellCoord;

enum CarvingDirection {
    CARVING_NORTH,
    CARVING_WEST,
    CARVING_SOUTH,
    CARVING_EAST
};

class MazeGrid {
private:
    int _width;
    int _height;

    CellCoord _entryPos;
    CellCoord _exitPos;

    std::map<int, std::vector<bool>> _adjacencyMatrix;
    std::map<int, std::vector<bool>> _visitedMatrix;

    std::map<CellCoord, Cell> _grid;

    std::default_random_engine _randomEngine;

public:
    MazeGrid()=delete;
    MazeGrid(const int width, const int height);
    MazeGrid(const int width, const int height, const CellCoord entryPos, const CellCoord exitPos, const bool allWallsBuilt);
    MazeGrid(const MazeGrid& m)=delete;

    ~MazeGrid();

    MazeGrid& operator=(const MazeGrid& m)=delete;


    void carve(const CellCoord src, const CellCoord dest);
    void carveToAllNeighbors(const CellCoord& cellCoord);
    CellCoord chooseRandomNeighbors(const CellCoord currentCell);
    bool isDeadEnd(const CellCoord cell);
    std::tuple<bool, CellCoord> hasVisitedNeighbor(const CellCoord cell);
    std::vector<CellCoord> getNeighbors(const CellCoord cell);

    void setVisited(const CellCoord cell);

    Cell getCell(const int row, const int col);
    Cell getCell(const CellCoord cell);
};

#endif