#include "MazeGraph.hpp"

#include <algorithm>
#include <iostream>
#include <stdexcept>

MazeGraph::MazeGraph(int w, int h, Cell entryPos, Cell exitPos)
    : _width(w)
    , _height(h)
    , _entryPos(entryPos)
    , _exitPos(exitPos)
    , _adjacencyList()
{
    carveToAllNeighbors(_entryPos);
    carveToAllNeighbors(_exitPos);
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

void MazeGraph::carve(const Cell src, const Cell dest)
{
    linkCells(src, dest);
    linkCells(dest, src);
}

void MazeGraph::carveToAllNeighbors(const Cell cell)
{
    auto neighbors = getSurroundingCells(cell);

    for (auto neighbor : neighbors) {
        carve(cell, neighbor);
    }
}

CellWalls MazeGraph::getCellWalls(Cell cell)
{
    CellWalls walls = {
        false,
        false,
        false,
        false
    };

    auto surrounding = getSurroundingCells(cell);

    // checking if cell is on sides
    if (cell != _entryPos && cell != _exitPos) {
        if (cell.isOnTopSide())
            walls.top = true;
        else if (cell.isOnBottomSide(_height))
            walls.bottom = true;

        if (cell.isOnRightSide(_width))
            walls.right = true;
        else if (cell.isOnLeftSide())
            walls.left = true;
    }

    for (auto neighbor : surrounding) {

        if (wallsBetween(cell, neighbor)) {
            if (cell.isLeftNeighbor(neighbor)) {
                walls.left = true;
                continue;
            }

            if (cell.isBottomNeighbor(neighbor, _height)) {
                walls.bottom = true;
                continue;
            }

            if (cell.isRightNeighbor(neighbor, _width)) {
                walls.right = true;
                continue;
            }

            if (cell.isTopNeighbor(neighbor)) {
                walls.top = true;
                continue;
            }
        }
    }

    return walls;
}