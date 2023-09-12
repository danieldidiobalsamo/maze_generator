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

    carveOutsideMaze(_entryPos);
    carveOutsideMaze(_exitPos);
}

void MazeGraph::carveOutsideMaze(Cell& cell)
{
    int index = mazeCoordToIndex(cell);

    _cells[index]._metadata.isPath = true;

    if (cell.getRow() == 0)
        _cells[index]._metadata.walls.top = false;
    else if (cell.getRow() == _height - 1)
        _cells[index]._metadata.walls.bottom = false;
    else if (cell.getCol() == 0)
        _cells[index]._metadata.walls.left = false;
    else if (cell.getCol() == _width - 1)
        _cells[index]._metadata.walls.right = false;
}

void MazeGraph::carve(int srcIndex, int destIndex)
{
    try {

        Cell src = indexToMazeCoord(srcIndex);
        Cell dest = indexToMazeCoord(destIndex);

        const bool carvingHorizontally = (src.getCol() != dest.getCol());
        const bool carvingVertically = (src.getRow() != dest.getRow());

        if (carvingHorizontally && carvingVertically)
            throw std::invalid_argument("Cells must be connected for carving");

        _adjacencyList[srcIndex].push_back(destIndex);
        _adjacencyList[destIndex].push_back(srcIndex);

        if (src.getCol() - 1 >= 0 && src.getCol() - 1 == dest.getCol()) {
            _cells[srcIndex]._metadata.walls.left = false;
            _cells[destIndex]._metadata.walls.right = false;
        } else if (src.getRow() + 1 < _height && src.getRow() + 1 == dest.getRow()) {
            _cells[srcIndex]._metadata.walls.bottom = false;
            _cells[destIndex]._metadata.walls.top = false;
        } else if (src.getCol() + 1 < _width && src.getCol() + 1 == dest.getCol()) {
            _cells[srcIndex]._metadata.walls.right = false;
            _cells[destIndex]._metadata.walls.left = false;
        } else if (src.getRow() - 1 >= 0 && src.getRow() - 1 == dest.getRow()) {
            _cells[srcIndex]._metadata.walls.top = false;
            _cells[destIndex]._metadata.walls.bottom = false;
        }

    } catch (const std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
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

int MazeGraph::mazeCoordToIndex(int row, int col)
{
    return (_width * row) + col;
}

Cell MazeGraph::indexToMazeCoord(int index)
{
    return Cell(index / _width, index % _width);
}

const unordered_map<int, vector<int>>& MazeGraph::getAdjacencyList()
{
    return _adjacencyList;
}

void MazeGraph::addToPath(int cellIndex)
{
    _cells[cellIndex]._metadata.isPath = true;
}