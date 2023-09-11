#include "EngineFacade.hpp"

#include <iostream>

EngineFacade::EngineFacade(const int w, const int h, const Cell& entryPos, const Cell& exitPos)
    : _maze(w, h, entryPos, exitPos)
{
}

void EngineFacade::generateMaze(const std::string& algo)
{
    if (algo == "hunt")
        huntAndKillGeneration();
    else if (algo == "backtracking")
        backtrackingGeneration();
    else {
        std::cout << "Bad algorithm name : " << algo << std::endl;
    }
}

void EngineFacade::huntAndKillGeneration()
{
    _maze.huntAndKill();
}

void EngineFacade::backtrackingGeneration()
{
    _maze.backtracking();
}

std::vector<CellMetadata> EngineFacade::getCellsMetadata()
{
    return _maze.getCellsMetadata();
}

void EngineFacade::solve()
{
    _maze.solveWithAStar();
}