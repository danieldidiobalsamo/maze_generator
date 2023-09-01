#pragma once

#include <emscripten/bind.h>
#include <functional>
#include <string>
#include <vector>

#include "EngineFacade.hpp"

EMSCRIPTEN_BINDINGS(CellWalls)
{
    emscripten::value_object<CellWalls>("CellWalls")
        .field("left", &CellWalls::left)
        .field("bottom", &CellWalls::bottom)
        .field("right", &CellWalls::right)
        .field("top", &CellWalls::top);
}

class Backend {

public:
    Backend();
    ~Backend();

    void generateMaze(int width, int height, std::string algo);
    const std::vector<CellWalls> getWallsList();

private:
    EngineFacade _engine;
    std::default_random_engine _randomIntGenerator; // must be init only once
};

EMSCRIPTEN_BINDINGS(Backend)
{
    emscripten::register_vector<CellWalls>("CellWallsLists");
    emscripten::class_<Backend>("Backend")
        .constructor<>()
        .function("generateMaze", std::function<void(Backend&, int, int, std::string)>(&Backend::generateMaze))
        .function("getWallsList", std::function<const std::vector<CellWalls>(Backend&)>(&Backend::getWallsList));
}