#include "Backend.hpp"

Backend::Backend()
    : _engine(0, 0, Cell(0, 0), Cell(0, 0))
    , _randomIntGenerator(static_cast<unsigned int>(time(0)))
{
}

void Backend::generateMaze(int width, int height, std::string algo)
{
    std::uniform_int_distribution<int> widthDistrib(0, width - 1);
    auto randomEntry = Cell(0, widthDistrib(_randomIntGenerator));

    auto exit = Cell(height - 1, width - 1);

    _engine = EngineFacade(width, height, randomEntry, exit);
    _engine.generateMaze(algo);
}

const std::vector<CellWalls> Backend::getWallsList()
{
    return _engine.getWallsList();
}