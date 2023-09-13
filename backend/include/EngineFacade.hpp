#pragma once

#ifdef EMCC_COMPILER
#include <emscripten/bind.h>
#endif

#include <functional>
#include <string>
#include <vector>

#include "Maze.hpp"

class EngineFacade {

public:
    EngineFacade();
    ~EngineFacade() = default;
    EngineFacade(const EngineFacade& backend) = delete;
    EngineFacade& operator=(const EngineFacade& backend) = delete;
    EngineFacade(EngineFacade&& backend) = delete;
    EngineFacade& operator=(EngineFacade&& backend) = delete;

    void generateMaze(int width, int height, const GenerationAlgo algo);
    void solve(const SolverAlgo algo);
    const std::vector<CellMetadata> getCellsMetadata();

private:
    Maze _maze;
    std::default_random_engine _randomIntGenerator; // must be init only once
};

#ifdef EMCC_COMPILER

// all of this shoudln't be considered when launching the unit tests (gcc, ctest), hence the flag

EMSCRIPTEN_BINDINGS(CellMetadata)
{
    emscripten::value_object<CellMetadata>("CellMetadata")
        .field("walls", &CellMetadata::walls)
        .field("isPath", &CellMetadata::isPath);
}

EMSCRIPTEN_BINDINGS(CellWalls)
{
    emscripten::value_object<CellWalls>("CellWalls")
        .field("left", &CellWalls::left)
        .field("bottom", &CellWalls::bottom)
        .field("right", &CellWalls::right)
        .field("top", &CellWalls::top);
}

EMSCRIPTEN_BINDINGS(EngineFacade)
{
    emscripten::register_vector<CellMetadata>("CellMetadataLists");
    emscripten::class_<EngineFacade>("EngineFacade")
        .constructor<>()
        .function("generateMaze", &EngineFacade::generateMaze)
        .function("getCellsMetadata", &EngineFacade::getCellsMetadata)
        .function("solve", &EngineFacade::solve);
}

EMSCRIPTEN_BINDINGS(GenerationAlgo)
{
    emscripten::enum_<GenerationAlgo>("GenerationAlgo")
        .value("HuntAndKill", GenerationAlgo::HuntAndKill)
        .value("Backtracking", GenerationAlgo::Backtracking);
}

EMSCRIPTEN_BINDINGS(SolverAlgo)
{
    emscripten::enum_<SolverAlgo>("SolverAlgo")
        .value("AStar", SolverAlgo::AStar)
        .value("Dijkstra", SolverAlgo::Dijkstra);
}

#endif