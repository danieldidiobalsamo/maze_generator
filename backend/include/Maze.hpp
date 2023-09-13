#pragma once

#include "GenerateBehavior.hpp"
#include "MazeGraph.hpp"

#include <memory>

class Maze {
private:
    int _width;
    int _height;

    Cell _entryPos;
    Cell _exitPos;

    MazeGraph _graph;

    std::unique_ptr<GenerateBehavior> _generateBehavior;

    int a_star_heuristic(int index);
    int euclidianDistance(int cellA, int cellB);

public:
    Maze() = delete;
    Maze(int width, int height, const Cell& entryPos, const Cell& exitPos);
    Maze(const Maze& m) = delete;
    ~Maze() = default;
    Maze(Maze&& facade) = delete;
    Maze& operator=(Maze&& maze) = delete;
    Maze& operator=(const Maze& m) = delete;

    void setParams(const int w, const int h, const Cell& entryPos, const Cell& exitPos);

    std::vector<CellMetadata> getCellsMetadata();

    void generate(std::string algo);

    bool solveWithAStar();
    void solveWithDijkstra();
};