#pragma once

#include <unordered_map>
#include <vector>

#include "MazeGraph.hpp"

// strategy design pattern for maze generators algorithms
class GenerateBehavior {

public:
    virtual void generate(MazeGraph& graph) = 0;
    virtual ~GenerateBehavior() {};
};