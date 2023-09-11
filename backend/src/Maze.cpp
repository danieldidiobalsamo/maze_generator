#include "Maze.hpp"

#include <iostream>
#include <limits>
#include <stdexcept>
#include <time.h>
#include <tuple>

Maze::Maze(int width, int height, const Cell& entryPos, const Cell& exitPos)
    : _width(width)
    , _height(height)
    , _entryPos(entryPos)
    , _exitPos(exitPos)
    , _graph(width, height, entryPos, exitPos)
    , _randomEngine(static_cast<unsigned int>(time(0)))
{
}

std::vector<CellMetadata> Maze::getCellsMetadata()
{
    return _graph.getCellsMetadata();
}

void Maze::huntAndKill()
{
    std::unordered_map<int, bool> visited;
    int nbCells = _width * _height;
    visited.reserve(nbCells);

    for (int cell = 0; cell < nbCells; ++cell) {
        visited[cell] = false;
    }

    int current = _graph.mazeCoordToIndex(_entryPos);
    visited[current] = true;

    int nextCell;
    bool allCellsTreated = false;
    bool huntMode = false;

    // looping on the whole maze
    do {

        do // looping until a dead end is reached
        {
            if (isDeadEnd(current, visited)) {
                // launching hunt mode
                huntMode = true;
            } else {
                // choosing an unvisited cell
                do {
                    nextCell = chooseRandomNeighbors(_graph.getSurroundingCells(current));
                } while (visited[nextCell]);

                visited[nextCell] = true;
                _graph.carve(current, nextCell);

                current = nextCell;
            }

        } while (!huntMode);

        // hunt mode
        // consists in searching for an unvisited cell which have at least a visited one
        // and searching row by row

        bool selectedCell = false;
        int row = 0;

        while (row < _height && !selectedCell) {
            int col = 0;

            while (col < _width && !selectedCell) {

                int tmpIndex = _graph.mazeCoordToIndex(row, col);
                if (visited[tmpIndex]) {
                    // checking if among its neighbors, there is one who is visited

                    auto [visitedNeighbor, chosenNeighbor] = hasVisitedNeighbor(tmpIndex, visited);

                    if (visitedNeighbor) {
                        current = tmpIndex;

                        _graph.carve(current, chosenNeighbor);
                        visited[current] = true;
                        selectedCell = true;
                    }
                }
                ++col;
            }

            ++row;
        }

        if (!selectedCell) {
            allCellsTreated = true;
        }

        huntMode = false;
    } while (!allCellsTreated);
}

bool Maze::isDeadEnd(int cellIndex, std::unordered_map<int, bool>& visited)
{
    auto [hasOne, neighbors] = hasVisitedNeighbor(cellIndex, visited);

    return !hasOne;
}

std::tuple<bool, int> Maze::hasVisitedNeighbor(int cellIndex, std::unordered_map<int, bool>& visited)
{
    std::vector<int> neighbors = _graph.getSurroundingCells(cellIndex);
    auto visitedNeighbor = std::find_if(neighbors.begin(), neighbors.end(),
        [&visited](int cell) {
            return !visited[cell];
        });

    if (visitedNeighbor != neighbors.end()) {
        return std::make_tuple(true, *visitedNeighbor);
    } else {
        return std::make_tuple(false, *visitedNeighbor);
    }
}

int Maze::chooseRandomNeighbors(const std::vector<int>& neighbors)
{
    std::uniform_int_distribution<int> intDistribution(0, static_cast<int>(neighbors.size() - 1));
    int randomIndex = intDistribution(_randomEngine);

    return neighbors[randomIndex];
}

bool Maze::solveWithAStar()
{
    std::vector<int> open; // used with std::make_heap as min heap
    open.push_back(_graph.mazeCoordToIndex(_entryPos));

    unordered_map<int, int> cameFrom;
    unordered_map<int, int> gScore;
    gScore.reserve(_width * _height);

    unordered_map<int, int> fScore;
    fScore.reserve(_width * _height);

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
            while (cameFrom.contains(current)) {
                current = cameFrom[current];
                _graph.addToPath(current);
            }

            return true;
        }

        std::pop_heap(open.begin(), open.end(), std::greater<> {});
        open.pop_back();
        auto neighbors = adjacencyList[current];

        for (auto neighbor = neighbors.begin(); neighbor != neighbors.end(); ++neighbor) {
            int tentativeGScore = gScore[current] + euclidianDistance(current, *neighbor);

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