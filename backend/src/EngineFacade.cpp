#include "EngineFacade.hpp"

#include <iostream>

EngineFacade::EngineFacade(const int w, const int h, const Cell& entryPos, const Cell& exitPos)
    : _maze(w, h, entryPos, exitPos)
{
}

void EngineFacade::generateMaze(const std::string& algo)
{
    _maze.generate(algo);
}

std::vector<CellMetadata> EngineFacade::getCellsMetadata()
{
    return _maze.getCellsMetadata();
}

void EngineFacade::solve(std::string algo)
{
    _maze.solve(algo);
}

void EngineFacade::setParams(const int w, const int h, const Cell& entryPos, const Cell& exitPos)
{
    _maze.setParams(w, h, entryPos, exitPos);
}