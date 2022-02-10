#ifndef MAZE_HPP
#define MAZE_HPP

#include "MazeGrid.hpp"

#include <utility> // pair

class Maze {
private:
    int _width;
    int _height;

    std::pair<int, int> _entryPos;
    std::pair<int, int> _exitPos;

    MazeGrid _grid;

public:
    Maze() = delete;
    Maze(int width, int height, std::pair<int, int> entryPos, std::pair<int, int> exitPos, bool initCellState);
    Maze(const Maze& m) = delete;
    ~Maze();

    Maze& operator=(const Maze& m) = delete;

    CellWalls getCellWalls(CellCoord cell);
    void visitCell(CellCoord cell);

    void huntAndKill();
};

#endif