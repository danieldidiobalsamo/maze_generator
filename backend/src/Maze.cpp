#include "Maze.hpp"

// generation algo
#include "Backtracking.hpp"
#include "HuntAndKill.hpp"

// solver algo
#include "AStar.hpp"
#include "Dijkstra.hpp"

#include <iostream>
#include <limits>
#include <random>
#include <set>
#include <stack>
#include <stdexcept>
#include <time.h>

Maze::Maze(int width, int height, const Cell& entryPos, const Cell& exitPos)
    : _graph(width, height, entryPos, exitPos)
{
    // default selected algorithms
    _generateBehavior = std::make_unique<Backtracking>();
    _solveBehavior = std::make_unique<AStar>();
}

std::vector<CellMetadata> Maze::getCellsMetadata()
{
    return _graph.getCellsMetadata();
}

void Maze::generate(std::string algo)
{
    if (algo == "hunt")
        _generateBehavior = std::make_unique<HuntAndKill>();
    else if (algo == "backtracking")
        _generateBehavior = std::make_unique<Backtracking>();
    else {
        std::cout << "Bad algorithm name : " << algo << std::endl;
    }

    _generateBehavior->generate(_graph);
}

bool Maze::solve(std::string algo)
{
    if (algo == "a_star")
        _solveBehavior = std::make_unique<AStar>();
    else if (algo == "dijkstra")
        _solveBehavior = std::make_unique<Dijkstra>();
    else {
        std::cout << "Bad solver name : " << algo << std::endl;
    }

    return _solveBehavior->solve(_graph);
}

void Maze::setParams(const int w, const int h, const Cell& entryPos, const Cell& exitPos)
{
    _graph.setParams(w, h, entryPos, exitPos);
}