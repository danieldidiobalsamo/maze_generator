#include "Dijkstra.hpp"
#include <set>
#include <stack>
#include <vector>

Dijkstra::~Dijkstra()
{
}

bool Dijkstra::solve(MazeGraph& graph)
{
    auto adjacencyList = graph.getAdjacencyList();

    int nbCells = graph.getWidth() * graph.getHeight();

    std::vector<int> dist;
    dist.reserve(nbCells);
    dist.assign(nbCells, std::numeric_limits<int>::max());
    int entryIndex = graph.mazeCoordToIndex(graph.getEntry());
    dist[entryIndex] = 0;

    std::vector<int> prev;
    prev.reserve(nbCells);
    prev.assign(nbCells, -1);

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

    int current = prev[graph.mazeCoordToIndex(graph.getExit())];

    do {
        graph.addToPath(current);
        current = prev[current];
    } while (current != entryIndex);

    return true;
}