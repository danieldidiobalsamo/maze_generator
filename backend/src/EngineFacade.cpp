#include "EngineFacade.hpp"

#include <iostream>

EngineFacade::EngineFacade(const int w, const int h, const Cell& entryPos, const Cell& exitPos)
    : _maze(w, h, entryPos, exitPos)
{
}

void EngineFacade::generateMaze(const std::string& algo)
{
    if (algo == "hunt")
        _maze.huntAndKill();
    else if (algo == "backtracking")
        _maze.backtracking();
    else {
        std::cout << "Bad algorithm name : " << algo << std::endl;
    }
}

std::vector<CellMetadata> EngineFacade::getCellsMetadata()
{
    return _maze.getCellsMetadata();
}

void EngineFacade::solve(std::string algo)
{
    if (algo == "a_star")
        _maze.solveWithAStar();
    else if (algo == "dijkstra")
        _maze.solveWithDijkstra();
    else {
        std::cout << "Bad solver name : " << algo << std::endl;
    }
}