#pragma once
#include "GenerateBehavior.hpp"

class Backtracking : public GenerateBehavior {
public:
    Backtracking() = default;
    virtual ~Backtracking();
    virtual void generate(MazeGraph& graph);
};
