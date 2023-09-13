#pragma once
#include "SolveBehavior.hpp"

class Dijkstra : public SolveBehavior {
public:
    Dijkstra() = default;
    virtual ~Dijkstra();
    virtual bool solve(MazeGraph& graph);
};
