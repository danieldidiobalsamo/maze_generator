#include "Maze.hpp"

#include <iostream>
#include <limits>
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
    , _randomEngine(static_cast<unsigned int>(time(0)))
{
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

        do // looping until a cell where all adjacents cells are visited
        {
            auto adjacents = getAdjacents(current, visited, false);

            if (adjacents.empty()) {
                // launching hunt mode
                huntMode = true;
            } else {
                // choosing an unvisited cell
                nextCell = chooseRandomAdjacent(adjacents);

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

                    auto adjacents = getAdjacents(tmpIndex, visited, false);

                    if (!adjacents.empty()) {
                        int adj = chooseRandomAdjacent(adjacents);

                        current = tmpIndex;
                        _graph.carve(current, adj);
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

void Maze::backtracking()
{
    std::unordered_map<int, bool> visited;
    int nbCells = _width * _height;
    visited.reserve(nbCells);

    for (int cell = 0; cell < nbCells; ++cell) {
        visited[cell] = false;
    }

    int entryIndex = _graph.mazeCoordToIndex(_entryPos);
    visited[entryIndex] = true;

    std::stack<int> cellStack;
    cellStack.push(entryIndex);
    int current = entryIndex;

    while (!cellStack.empty()) {
        auto adjacents = getAdjacents(current, visited, false);

        if (adjacents.empty()) {
            current = cellStack.top();
            cellStack.pop();
        } else {
            int neighbor = chooseRandomAdjacent(adjacents);
            _graph.carve(current, neighbor);

            visited[neighbor] = true;
            cellStack.push(neighbor);
            current = neighbor;
        }
    }
}

std::vector<int> Maze::getAdjacents(int cellIndex, std::unordered_map<int, bool>& visited, bool visitedValue)
{
    Cell cell = _graph.indexToMazeCoord(cellIndex);
    std::vector<int> surrounding;

    int row = cell.getRow();
    int col = cell.getCol();

    int top = _graph.mazeCoordToIndex(row - 1, col);
    int bottom = _graph.mazeCoordToIndex(row + 1, col);
    int left = _graph.mazeCoordToIndex(row, col - 1);
    int right = _graph.mazeCoordToIndex(row, col + 1);

    if (row - 1 >= 0 && visited[top] == visitedValue)
        surrounding.push_back(top);
    if (row + 1 < _height && visited[bottom] == visitedValue)
        surrounding.push_back(bottom);
    if (col - 1 >= 0 && visited[left] == visitedValue)
        surrounding.push_back(left);
    if (col + 1 < _width && visited[right] == visitedValue)
        surrounding.push_back(right);

    return surrounding;
}

int Maze::chooseRandomAdjacent(vector<int>& adjacents)
{
    try {
        if (adjacents.empty()) {
            throw std::out_of_range("Adjacent cells vector is empty");
        }
    } catch (const std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
    }

    std::uniform_int_distribution<int> intDistribution(0, static_cast<int>(adjacents.size() - 1));
    int randomIndex = intDistribution(_randomEngine);

    return adjacents[randomIndex];
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