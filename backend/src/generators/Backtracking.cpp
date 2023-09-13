#include "Backtracking.hpp"
#include <stack>
#include <unordered_map>

Backtracking::~Backtracking()
{
}

void Backtracking::generate(MazeGraph& graph)
{
    std::unordered_map<int, bool> visited;
    int nbCells = graph.getWidth() * graph.getHeight();
    visited.reserve(nbCells);

    for (int cell = 0; cell < nbCells; ++cell) {
        visited[cell] = false;
    }

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