#include "MazeGraph.hpp"

#include <iostream>
#include <stdexcept>

MazeGraph::MazeGraph(int w, int h, bool initCellState)
    : _width(w)
    , _height(h)
{
    const int nbCell = _width * _height;

    for (int row = 0; row < nbCell; ++row) {
        for (int col = 0; col < nbCell; ++col) {
            _adjacencyMatrix[row].push_back(initCellState);
        }
    }

    for (int row = 0; row < _height; ++row) {
        for (int col = 0; col < _width; ++col) {
            _visitedMatrix[row].push_back(false);
        }
    }
}

MazeGraph::~MazeGraph()
{
}

void MazeGraph::linkCells(Cell src, Cell dest)
{
    try {
        const bool carvingHorizontally = (src.getCol() != dest.getCol());
        const bool carvingVertically = (src.getRow() != dest.getRow());

        // exception
        if (carvingHorizontally && carvingVertically)
            throw std::invalid_argument("Cells must be connected for carving");

        int srcIndex = mazeCoordToIndex(src);
        int destIndex = mazeCoordToIndex(dest);

        _adjacencyMatrix[srcIndex].at(destIndex) = true;
        _adjacencyMatrix[destIndex].at(srcIndex) = true;

    } catch (const std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
    }
}

bool MazeGraph::areCellsLinked(Cell src, Cell dest)
{
    const int srcIndex = mazeCoordToIndex(src);
    const int destIndex = mazeCoordToIndex(dest);

    return _adjacencyMatrix[srcIndex][destIndex];
}

int MazeGraph::mazeCoordToIndex(Cell coord)
{
    return (_width * coord.getRow()) + coord.getCol();
}

bool MazeGraph::isCellVisited(Cell cell)
{
    return _visitedMatrix[cell.getRow()][cell.getCol()];
}

void MazeGraph::setVisited(Cell cell)
{
    _visitedMatrix[cell.getRow()][cell.getCol()] = true;
}