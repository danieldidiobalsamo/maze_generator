#pragma once

#include <emscripten/bind.h>
#include <functional>
#include <string>
#include <vector>

#include "EngineFacade.hpp"

class Backend {

public:
    Backend();
    ~Backend() = default;
    Backend(const Backend& backend) = default;
    Backend& operator=(const Backend& backend) = default;
    Backend(Backend&& backend) = default;
    Backend& operator=(Backend&& backend) = default;

    void generateMaze(int width, int height, std::string algo);
    const std::vector<CellMetadata> getCellsMetadata();

private:
    EngineFacade _engine;
    std::default_random_engine _randomIntGenerator; // must be init only once
};

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

EMSCRIPTEN_BINDINGS(Backend)
{
    emscripten::register_vector<CellMetadata>("CellMetadataLists");
    emscripten::class_<Backend>("Backend")
        .constructor<>()
        .function("generateMaze", std::function<void(Backend&, int, int, std::string)>(&Backend::generateMaze))
        .function("getCellsMetadata", std::function<const std::vector<CellMetadata>(Backend&)>(&Backend::getCellsMetadata));
}
