#include "Backtracking.hpp"
#include <stack>
#include <vector>

Backtracking::~Backtracking()
{
}

void Backtracking::generate(MazeGraph& graph)
{
    std::vector<bool> visited;
    int nbCells = graph.getWidth() * graph.getHeight();
    visited.reserve(nbCells);
    visited.assign(nbCells, false);

    int entryIndex = graph.mazeCoordToIndex(graph.getEntry());
    visited[entryIndex] = true;

    std::stack<int> cellStack;
    cellStack.push(entryIndex);
    int current = entryIndex;

    while (!cellStack.empty()) {
        auto adjacents = graph.getAdjacents(current, visited, false);

        if (adjacents.empty()) {
            current = cellStack.top();
            cellStack.pop();
        } else {
            int neighbor = graph.chooseRandomAdjacent(adjacents);
            graph.carve(current, neighbor);

            visited[neighbor] = true;
            cellStack.push(neighbor);
            current = neighbor;
        }
    }
}