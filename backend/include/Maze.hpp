#pragma once

#include "MazeGrid.hpp"

class Maze {
private:
    int _width;
    int _height;

    CellCoord _entryPos;

    MazeGrid _grid;

public:
    Maze() = delete;
    Maze(int width, int height, CellCoord entryPos, CellCoord exitPos, bool initCellState);
    Maze(const Maze& m) = delete;
    ~Maze();

    Maze& operator=(const Maze& m) = delete;

    CellWalls getCellWalls(CellCoord cell);
    void visitCell(CellCoord cell);

    void huntAndKill();
};