#pragma once
#include "GenerateBehavior.hpp"

class HuntAndKill : public GenerateBehavior {
public:
    HuntAndKill() = default;
    virtual ~HuntAndKill();
    virtual void generate(MazeGraph& graph);
};
