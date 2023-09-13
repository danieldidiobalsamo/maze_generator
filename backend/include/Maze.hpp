#pragma once

#include "GenerateBehavior.hpp"
#include "MazeGraph.hpp"
#include "SolveBehavior.hpp"

#include <memory>

class Maze {
private:
    MazeGraph _graph;

    std::unique_ptr<GenerateBehavior> _generateBehavior;
    std::unique_ptr<SolveBehavior> _solveBehavior;

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
    bool solve(std::string algo);
};