#include "MazeGraph.hpp"

#include <iostream>
#include <stdexcept>

MazeGraph::MazeGraph(int w, int h)
    : _width(w)
    , _height(h)
    , _adjacencyList()
{
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

        _adjacencyList[src].push_back(dest);
        _adjacencyList[dest].push_back(src);

    } catch (const std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
    }
}

bool MazeGraph::wallsBetween(Cell src, Cell dest)
{
    std::vector<Cell>::iterator cell = std::find_if(_adjacencyList[src].begin(), _adjacencyList[src].end(),
        [=](const Cell& cell) {
            return cell == dest;
        });

    return cell == _adjacencyList[src].end();
}

bool MazeGraph::isCellVisited(Cell cell)
{
    return _visitedMatrix[cell.getRow()][cell.getCol()];
}

void MazeGraph::setVisited(Cell cell)
{
    _visitedMatrix[cell.getRow()][cell.getCol()] = true;
}

vector<Cell> MazeGraph::getSurroundingCells(Cell cell)
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