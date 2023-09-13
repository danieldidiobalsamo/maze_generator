#include "Backend.hpp"

Backend::Backend()
    : _engine(10, 10, Cell(0, 0), Cell(9, 9))
    , _randomIntGenerator(static_cast<unsigned int>(time(0)))
{
}

void Backend::generateMaze(int width, int height, std::string algo)
{
    Cell entry {}, exit {};
    std::uniform_int_distribution<int> intDistrib(0, 10);

    if (intDistrib(_randomIntGenerator) <= 5) {
        // entry on top, exit on bottom
        std::uniform_int_distribution<int> distrib(0, width - 1);

        entry = Cell(0, distrib(_randomIntGenerator));
        exit = Cell(height - 1, distrib(_randomIntGenerator));

    } else {
        // entry on left, exit on right
        std::uniform_int_distribution<int> distrib(0, height - 1);

        entry = Cell(distrib(_randomIntGenerator), 0);
        exit = Cell(distrib(_randomIntGenerator), width - 1);
    }

    _engine = EngineFacade(width, height, entry, exit);
    _engine.generateMaze(algo);
}

const std::vector<CellMetadata> Backend::getCellsMetadata()
{
    return _engine.getCellsMetadata();
}

void Backend::solve(const std::string algo)
{
    _engine.solve(algo);
}