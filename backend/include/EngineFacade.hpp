#pragma once

#include "Maze.hpp"

#include <string>

class EngineFacade {
private:
    Maze _maze;

public:
    EngineFacade() = delete;
    EngineFacade(const int w, const int h);
    EngineFacade(const int w, const int h, const Cell& entryPos, const Cell& exitPos);
    EngineFacade(const EngineFacade& e) = delete;
    EngineFacade& operator=(const EngineFacade& f) = delete;
    ~EngineFacade() = default;
    EngineFacade(EngineFacade&& facade) = delete;
    EngineFacade& operator=(EngineFacade&& facade) = delete;

    void setParams(const int w, const int h, const Cell& entryPos, const Cell& exitPos);

    void initMaze();
    void generateMaze(const std::string& algo);
    void solve(const std::string algo);

    std::vector<CellMetadata> getCellsMetadata();
};