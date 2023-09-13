#pragma once

#include <unordered_map>
#include <vector>

#include "MazeGraph.hpp"

// strategy design pattern for maze solver algorithms
class SolveBehavior {

public:
    virtual bool solve(MazeGraph& graph) = 0;
    virtual ~SolveBehavior() {};
};