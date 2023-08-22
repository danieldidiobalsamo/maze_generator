#pragma once

#include "Maze.hpp"

#include <string>
#include <utility>

class EngineFacade {
private:
    int _mazeWidth;
    int _mazeHeight;
    Cell _entryPos;
    Cell _exitPos;
    Maze _maze;

public:
    EngineFacade() = delete;
    EngineFacade(const int w, const int h);
    EngineFacade(const int w, const int h, const Cell entryPos, const Cell exitPos, const bool initCellState);
    ~EngineFacade();

    EngineFacade& operator=(const EngineFacade& f) = delete;

    void initMaze();
    void generateMaze(const std::string& algo);

    // generation algo

    void huntAndKillGeneration();
    void recursiveBacktrace();

    Maze& getMaze();
};