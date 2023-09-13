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

    void generateMaze(int width, int height, std::string algo);
    void solve(std::string algo);
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
        .function("generateMaze", std::function<void(EngineFacade&, int, int, std::string)>(&EngineFacade::generateMaze))
        .function("getCellsMetadata", std::function<const std::vector<CellMetadata>(EngineFacade&)>(&EngineFacade::getCellsMetadata))
        .function("solve", &EngineFacade::solve);
}

#endif