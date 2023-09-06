#include "MazeGraph.hpp"

#include <algorithm>
#include <iostream>
#include <stdexcept>

MazeGraph::MazeGraph(int w, int h, const Cell& entryPos, const Cell& exitPos)
    : _width(w)
    , _height(h)
    , _entryPos(entryPos)
    , _exitPos(exitPos)
    , _adjacencyList()
{

    _cellsMetadata.reserve(_width * _height);
    for (int i = 0; i < _width * _height; ++i) {
        _cellsMetadata.push_back(CellMetadata { CellWalls { true, true, true, true }, false });
    }

    _cellsMetadata[mazeCoordToIndex(_entryPos)] = CellMetadata { CellWalls { false, false, false, false }, true };
    _cellsMetadata[mazeCoordToIndex(_exitPos)] = CellMetadata { CellWalls { false, false, false, false }, true };

    carveToAllNeighbors(_entryPos);
    carveToAllNeighbors(_exitPos);
}

vector<Cell> MazeGraph::getSurroundingCells(const Cell& cell)
{
    std::vector<Cell> surrouding; // not necessary neighbors, just cells around

    if (cell.getRow() - 1 >= 0)
        surrouding.push_back(cell.getTopNeighbor());
    if (cell.getRow() + 1 < _height)
        surrouding.push_back(cell.getBottomNeighbor(_height));
    if (cell.getCol() - 1 >= 0)
        surrouding.push_back(cell.getLeftNeighbor());
    if (cell.getCol() + 1 < _width)
        surrouding.push_back(cell.getRightNeighbor(_width));

    return surrouding;
}

void MazeGraph::carve(const Cell& src, const Cell& dest)
{
    try {
        const bool carvingHorizontally = (src.getCol() != dest.getCol());
        const bool carvingVertically = (src.getRow() != dest.getRow());

        if (carvingHorizontally && carvingVertically)
            throw std::invalid_argument("Cells must be connected for carving");

        _adjacencyList[src].push_back(dest);
        _adjacencyList[dest].push_back(src);

        if (src.isLeftNeighbor(dest)) {
            _cellsMetadata[mazeCoordToIndex(src)].walls.left = false;
            _cellsMetadata[mazeCoordToIndex(dest)].walls.right = false;
        } else if (src.isBottomNeighbor(dest, _height)) {
            _cellsMetadata[mazeCoordToIndex(src)].walls.bottom = false;
            _cellsMetadata[mazeCoordToIndex(dest)].walls.top = false;
        } else if (src.isRightNeighbor(dest, _width)) {
            _cellsMetadata[mazeCoordToIndex(src)].walls.right = false;
            _cellsMetadata[mazeCoordToIndex(dest)].walls.left = false;
        } else if (src.isTopNeighbor(dest)) {
            _cellsMetadata[mazeCoordToIndex(src)].walls.top = false;
            _cellsMetadata[mazeCoordToIndex(dest)].walls.bottom = false;
        }

    } catch (const std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
    }
}

void MazeGraph::carveToAllNeighbors(const Cell& cell)
{
    auto neighbors = getSurroundingCells(cell);

    for (auto neighbor : neighbors) {
        carve(cell, neighbor);
    }
}

vector<CellMetadata> MazeGraph::getCellsMetadata()
{
    return _cellsMetadata;
}

int MazeGraph::mazeCoordToIndex(const Cell& coord)
{
    return (_width * coord.getRow()) + coord.getCol();
}