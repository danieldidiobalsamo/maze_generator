#pragma once

#include "MazeGrid.hpp"

class Maze {
private:
    int _width;
    int _height;

    Cell _entryPos;

    MazeGrid _grid;

public:
    Maze() = delete;
    Maze(int width, int height, Cell entryPos, Cell exitPos, bool initCellState);
    Maze(const Maze& m) = default;
    ~Maze();

    Maze& operator=(const Maze& m) = default;

    CellWalls getCellWalls(Cell cell);
    void visitCell(Cell cell);

    void huntAndKill();
};