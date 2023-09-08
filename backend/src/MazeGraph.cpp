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

    _cells.reserve(_width * _height);

    for (int row = 0; row < _height; ++row) {
        for (int col = 0; col < _width; ++col) {
            _cells.push_back(Cell(row, col, CellMetadata { CellWalls { true, true, true, true }, false }));
        }
    }

    _cells[mazeCoordToIndex(_entryPos)]._metadata = CellMetadata { CellWalls { false, false, false, false }, true };
    _cells[mazeCoordToIndex(_exitPos)]._metadata = CellMetadata { CellWalls { false, false, false, false }, true };

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

        int srcIndex = mazeCoordToIndex(src);
        int destIndex = mazeCoordToIndex(dest);

        _adjacencyList[srcIndex].push_back(destIndex);
        _adjacencyList[destIndex].push_back(srcIndex);

        if (src.isLeftNeighbor(dest)) {
            _cells[mazeCoordToIndex(src)]._metadata.walls.left = false;
            _cells[mazeCoordToIndex(dest)]._metadata.walls.right = false;
        } else if (src.isBottomNeighbor(dest, _height)) {
            _cells[mazeCoordToIndex(src)]._metadata.walls.bottom = false;
            _cells[mazeCoordToIndex(dest)]._metadata.walls.top = false;
        } else if (src.isRightNeighbor(dest, _width)) {
            _cells[mazeCoordToIndex(src)]._metadata.walls.right = false;
            _cells[mazeCoordToIndex(dest)]._metadata.walls.left = false;
        } else if (src.isTopNeighbor(dest)) {
            _cells[mazeCoordToIndex(src)]._metadata.walls.top = false;
            _cells[mazeCoordToIndex(dest)]._metadata.walls.bottom = false;
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
    vector<CellMetadata> metadataList;

    for (auto i = _cells.begin(); i != _cells.end(); ++i) {
        metadataList.push_back(i->_metadata);
    }

    return metadataList;
}

int MazeGraph::mazeCoordToIndex(const Cell& coord)
{
    return (_width * coord.getRow()) + coord.getCol();
}

Cell MazeGraph::indexToMazeCoord(int index)
{
    return Cell(index % _width, index / _width);
}

const unordered_map<int, vector<int>>& MazeGraph::getAdjacencyList()
{
    return _adjacencyList;
}

void MazeGraph::addToPath(int cellIndex)
{
    _cells[cellIndex]._metadata.isPath = true;
}