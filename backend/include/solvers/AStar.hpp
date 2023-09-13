#pragma once
#include "SolveBehavior.hpp"

class AStar : public SolveBehavior {
private:
    int heuristic(Cell& cell, Cell& exit);

public:
    AStar() = default;
    virtual ~AStar();
    virtual bool solve(MazeGraph& graph);
};
