#pragma once

#include <utility>
#include <string>
#include <vector>

#include "EngineFacade.hpp"

class BackEnd {

public:
    BackEnd();
    ~BackEnd();

    void setMazeWidth(int _width);
    void setMazeHeight(int _height);
    void setAlgo(std::string algo);
    void generateMaze();
    std::vector<bool> getCell(int row, int col);

private:
    EngineFacade* _engine;

    int _mazeWidth;
    int _mazeHeight;
    CellCoord _entryPos;
    CellCoord _exitPos;

    std::string _algo;

    std::default_random_engine _randomIntGenerator;
};