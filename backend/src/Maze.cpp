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

void Maze::generate(GenerationAlgo algo)
{
    switch (algo) {

    case GenerationAlgo::HuntAndKill:
        _generateBehavior = std::make_unique<HuntAndKill>();
        break;
    case GenerationAlgo::Backtracking:
        _generateBehavior = std::make_unique<Backtracking>();
        break;
    default:
        std::cout << "Bad maze generator name" << std::endl;
    }

    _generateBehavior->generate(_graph);
}

bool Maze::solve(SolverAlgo algo)
{
    switch (algo) {
    case SolverAlgo::AStar:
        _solveBehavior = std::make_unique<AStar>();
        break;
    case SolverAlgo::Dijkstra:
        _solveBehavior = std::make_unique<Dijkstra>();
        break;
    default:
        std::cout << "Bad maze solver name" << std::endl;
    }

    return _solveBehavior->solve(_graph);
}

void Maze::setParams(const int w, const int h, const Cell& entryPos, const Cell& exitPos)
{
    _graph.setParams(w, h, entryPos, exitPos);
}