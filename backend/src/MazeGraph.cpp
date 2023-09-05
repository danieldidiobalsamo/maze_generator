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

    _wallsList.reserve(_width * _height);
    for (int i = 0; i < _width * _height; ++i) {
        _wallsList.push_back(CellWalls { true, true, true, true });
    }

    _wallsList[mazeCoordToIndex(_entryPos)] = CellWalls { false, false, false, false };
    _wallsList[mazeCoordToIndex(_exitPos)] = CellWalls { false, false, false, false };

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
            _wallsList[mazeCoordToIndex(src)].left = false;
            _wallsList[mazeCoordToIndex(dest)].right = false;
        } else if (src.isBottomNeighbor(dest, _height)) {
            _wallsList[mazeCoordToIndex(src)].bottom = false;
            _wallsList[mazeCoordToIndex(dest)].top = false;
        } else if (src.isRightNeighbor(dest, _width)) {
            _wallsList[mazeCoordToIndex(src)].right = false;
            _wallsList[mazeCoordToIndex(dest)].left = false;
        } else if (src.isTopNeighbor(dest)) {
            _wallsList[mazeCoordToIndex(src)].top = false;
            _wallsList[mazeCoordToIndex(dest)].bottom = false;
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

vector<CellWalls> MazeGraph::getWallsList()
{
    return _wallsList;
}

int MazeGraph::mazeCoordToIndex(const Cell& coord)
{
    return (_width * coord.getRow()) + coord.getCol();
}