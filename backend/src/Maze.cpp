#include "Maze.hpp"

// generation algo
#include "Backtracking.hpp"
#include "HuntAndKill.hpp"

#include <iostream>
#include <limits>
#include <random>
#include <set>
#include <stack>
#include <stdexcept>
#include <time.h>

Maze::Maze(int width, int height, const Cell& entryPos, const Cell& exitPos)
    : _width(width)
    , _height(height)
    , _entryPos(entryPos)
    , _exitPos(exitPos)
    , _graph(width, height, entryPos, exitPos)
{
    _generateBehavior = std::make_unique<Backtracking>();
}

Maze::~Maze()
{
    _generateBehavior.reset();
}

bool Maze::solveWithAStar()
{
    std::vector<int> open; // used with std::make_heap as min heap
    open.push_back(_graph.mazeCoordToIndex(_entryPos));

    int nbCells = _width * _height;

    std::vector<int> cameFrom;
    cameFrom.reserve(nbCells);
    cameFrom.assign(nbCells, -1);

    std::vector<int> gScore;
    gScore.reserve(nbCells);

    std::vector<int> fScore;
    fScore.reserve(nbCells);

    for (int i = 0; i < _width * _height; ++i) {
        gScore[i] = std::numeric_limits<int>::max();
        fScore[i] = std::numeric_limits<int>::max();
    }

    int entry = _graph.mazeCoordToIndex(_entryPos);
    int exit = _graph.mazeCoordToIndex(_exitPos);
    gScore[entry] = 0;
    fScore[entry] = a_star_heuristic(entry);

    auto adjacencyList = _graph.getAdjacencyList();

    while (!open.empty()) {
        int current = open.front();

        if (current == exit) {
            _graph.addToPath(current);
            while (cameFrom[current] != -1) {
                current = cameFrom[current];
                _graph.addToPath(current);
            }

            return true;
        }

        std::pop_heap(open.begin(), open.end(), std::greater<> {});
        open.pop_back();
        auto neighbors = adjacencyList[current];

        for (auto neighbor = neighbors.begin(); neighbor != neighbors.end(); ++neighbor) {
            int tentativeGScore = gScore[current] + 1;

            if (tentativeGScore < gScore[*neighbor]) {
                cameFrom[*neighbor] = current;
                gScore[*neighbor] = tentativeGScore;
                fScore[*neighbor] = tentativeGScore + a_star_heuristic(*neighbor);

                if (std::find(open.begin(), open.end(), *neighbor) == open.end()) {
                    open.push_back(*neighbor);
                    std::make_heap(open.begin(), open.end(), std::greater<> {});
                }
            }
        }
    }

    return false; // no solution
}

int Maze::euclidianDistance(int cellA, int cellB)
{
    Cell a = _graph.indexToMazeCoord(cellA);
    Cell b = _graph.indexToMazeCoord(cellB);

    return (a.getRow() - b.getRow()) * (a.getRow() - b.getRow()) + (a.getCol() - b.getCol()) * (a.getCol() - b.getCol());
}

int Maze::a_star_heuristic(int index)
{
    return euclidianDistance(index, _graph.mazeCoordToIndex(_exitPos));
}

std::vector<CellMetadata> Maze::getCellsMetadata()
{
    return _graph.getCellsMetadata();
}

void Maze::solveWithDijkstra()
{
    auto adjacencyList = _graph.getAdjacencyList();

    int nbCells = _width * _height;

    std::vector<int> dist;
    dist.reserve(nbCells);
    dist.assign(nbCells, std::numeric_limits<int>::max());
    dist[_graph.mazeCoordToIndex(_entryPos)] = 0;

    std::vector<int> prev;
    prev.reserve(nbCells);
    prev.assign(nbCells, -1);

    int entryIndex = _graph.mazeCoordToIndex(_entryPos);

    std::set<std::pair<int, int>> nodes;
    nodes.insert({ 0, entryIndex });

    while (!nodes.empty()) {
        int current = nodes.begin()->second;
        nodes.erase(nodes.begin());

        auto neighbors = adjacencyList[current];
        for (auto n = neighbors.begin(); n != neighbors.end(); ++n) {
            int alt = dist[current] + 1;

            if (alt < dist[*n]) {
                dist[*n] = alt;
                prev[*n] = current;
                nodes.insert({ dist[*n], *n });
            }
        }
    }

    int current = prev[_graph.mazeCoordToIndex(_exitPos)];

    do {
        _graph.addToPath(current);
        current = prev[current];
    } while (current != entryIndex);
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