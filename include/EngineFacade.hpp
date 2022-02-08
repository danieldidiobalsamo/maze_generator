#ifndef ENGINE_FACADE_HPP
#define ENGINE_FACADE_HPP

#include "Maze.hpp"

#include <string>
#include <utility>

class EngineFacade {
private:
    int _mazeWidth;
    int _mazeHeight;
    CellCoord _entryPos;
    CellCoord _exitPos;
    Maze _maze;

public:
    EngineFacade();
    EngineFacade(const int w, const int h);
    EngineFacade(const int w, const int h, const CellCoord entryPos, const CellCoord exitPos, const bool allWallsBuilt);
    ~EngineFacade();

    EngineFacade& operator=(const EngineFacade& f);

    void initMaze();
    void generateMaze(const std::string algo);

    // generation algo

    void huntAndKillGeneration();
    void recursiveBacktrace();

    Maze& getMaze();
};

#endif