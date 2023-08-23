#include "EngineFacade.hpp"

#include <iostream>

EngineFacade::EngineFacade(const int w, const int h, const Cell entryPos, const Cell exitPos, const bool initCellState)
    : _maze(w, h, entryPos, exitPos, initCellState)
{
}

EngineFacade::~EngineFacade()
{
}

void EngineFacade::generateMaze(const std::string& algo)
{
    if (algo == "Hunt and kill")
        huntAndKillGeneration();
    else {
        std::cout << "Bad algorithm name : " << algo << std::endl;
    }
}

void EngineFacade::huntAndKillGeneration()
{
    _maze.huntAndKill();
}

Maze& EngineFacade::getMaze()
{
    return _maze;
}