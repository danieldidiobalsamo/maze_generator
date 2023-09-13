#include "HuntAndKill.hpp"
#include "GenerateBehavior.hpp"

HuntAndKill::~HuntAndKill()
{
}

void HuntAndKill::generate(MazeGraph& graph)
{
    int width = graph.getWidth();
    int height = graph.getHeight();

    std::unordered_map<int, bool> visited;
    int nbCells = width * height;
    visited.reserve(nbCells);

    for (int cell = 0; cell < nbCells; ++cell) {
        visited[cell] = false;
    }

    int current = graph.mazeCoordToIndex(graph.getEntry());
    visited[current] = true;

    int nextCell;
    bool allCellsTreated = false;
    bool huntMode = false;

    // looping on the whole maze
    do {

        do // looping until a cell where all adjacents cells are visited
        {
            auto adjacents = graph.getAdjacents(current, visited, false);

            if (adjacents.empty()) {
                // launching hunt mode
                huntMode = true;
            } else {
                // choosing an unvisited cell
                nextCell = graph.chooseRandomAdjacent(adjacents);

                visited[nextCell] = true;
                graph.carve(current, nextCell);

                current = nextCell;
            }

        } while (!huntMode);

        // hunt mode
        // consists in searching for an unvisited cell which have at least a visited one
        // and searching row by row

        bool selectedCell = false;
        int row = 0;

        while (row < height && !selectedCell) {
            int col = 0;

            while (col < width && !selectedCell) {

                int tmpIndex = graph.mazeCoordToIndex(row, col);

                if (visited[tmpIndex]) {
                    // checking if among its neighbors, there is one who is visited

                    auto adjacents = graph.getAdjacents(tmpIndex, visited, false);

                    if (!adjacents.empty()) {
                        int adj = graph.chooseRandomAdjacent(adjacents);

                        current = tmpIndex;
                        graph.carve(current, adj);
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