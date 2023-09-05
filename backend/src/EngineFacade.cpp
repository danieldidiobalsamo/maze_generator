#include "EngineFacade.hpp"

#include <iostream>

EngineFacade::EngineFacade(const int w, const int h, const Cell entryPos, const Cell exitPos)
    : _maze(w, h, entryPos, exitPos)
{
}

void EngineFacade::generateMaze(const std::string& algo)
{
    if (algo == "hunt")
        huntAndKillGeneration();
    else {
        std::cout << "Bad algorithm name : " << algo << std::endl;
    }
}

void EngineFacade::huntAndKillGeneration()
{
    _maze.huntAndKill();
}

std::vector<CellWalls> EngineFacade::getWallsList()
{
    return _maze.getWallsList();
}