#include "AStar.hpp"
#include <stack>
#include <unordered_map>

AStar::~AStar()
{
}

bool AStar::solve(MazeGraph& graph)
{
    Cell entryCell = graph.getEntry();
    Cell exitCell = graph.getExit();

    int entry = graph.mazeCoordToIndex(entryCell);
    int exit = graph.mazeCoordToIndex(graph.getExit());

    std::vector<int> open; // used with std::make_heap as min heap
    open.push_back(entry);

    int nbCells = graph.getWidth() * graph.getHeight();

    std::vector<int> cameFrom;
    cameFrom.reserve(nbCells);
    cameFrom.assign(nbCells, -1);

    std::vector<int> gScore;
    gScore.reserve(nbCells);

    std::vector<int> fScore;
    fScore.reserve(nbCells);

    for (int i = 0; i < nbCells; ++i) {
        gScore[i] = std::numeric_limits<int>::max();
        fScore[i] = std::numeric_limits<int>::max();
    }

    gScore[entry] = 0;
    fScore[entry] = heuristic(entryCell, exitCell);

    auto adjacencyList = graph.getAdjacencyList();

    while (!open.empty()) {
        int current = open.front();

        if (current == exit) {
            graph.addToPath(current);
            while (cameFrom[current] != -1) {
                current = cameFrom[current];
                graph.addToPath(current);
            }

            return true;
        }

        std::pop_heap(open.begin(), open.end(), std::greater<> {});
        open.pop_back();
        auto neighbors = adjacencyList[current];

        for (auto neighbor = neighbors.begin(); neighbor != neighbors.end(); ++neighbor) {
            int tentativeGScore = gScore[current] + 1;

            if (tentativeGScore < gScore[*neighbor]) {

                auto neighborCell = graph.indexToMazeCoord(*neighbor);
                cameFrom[*neighbor] = current;
                gScore[*neighbor] = tentativeGScore;
                fScore[*neighbor] = tentativeGScore + heuristic(neighborCell, exitCell);

                if (std::find(open.begin(), open.end(), *neighbor) == open.end()) {
                    open.push_back(*neighbor);
                    std::make_heap(open.begin(), open.end(), std::greater<> {});
                }
            }
        }
    }

    return false; // no solution
}

int AStar::heuristic(Cell& cell, Cell& exit)
{
    return (cell.getRow() - exit.getRow()) * (cell.getRow() - exit.getRow()) + (cell.getCol() - exit.getCol()) * (cell.getCol() - exit.getCol());
}
