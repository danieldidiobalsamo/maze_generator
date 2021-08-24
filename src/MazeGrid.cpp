#include "MazeGrid.hpp"

#include <iostream>
#include <stdexcept>

MazeGrid::MazeGrid() : _randomEngine(static_cast<unsigned int>(time(0))) // used to generate random int, better than rand()
{
	_width = 0;
	_height = 0;
}

MazeGrid::MazeGrid(const int width, const int height) : _randomEngine(static_cast<unsigned int>(time(0))) // used to generate random int, better than rand()
{
	_width = width;
	_height = height;
}

MazeGrid::MazeGrid(const int width, const int height, const CellCoord entryPos, const CellCoord exitPos, bool allWallsBuilt) : _randomEngine(static_cast<unsigned int>(time(0))) // used to generate random int, better than rand()
{
	_width = width;
	_height = height;

	_entryPos = entryPos;
	_exitPos = exitPos;

	for (int row = 0; row < height; ++row)
	{
		// determining if the cell is an entry, exit or normal cell
		for (int col = 0; col < width; ++col)
		{
			auto current = std::make_pair(row, col);

			if(entryPos.first == row && entryPos.second == col) // cell is entry
				_grid[current] = Cell(row, col, false, true, false);
			
			else if(exitPos.first == row && exitPos.second == col)// cell is exit
			{
				_grid[current] = Cell(row, col, false, false, true);
			}
			
			else // cell is a normal cell
				_grid[current] = Cell(row, col, allWallsBuilt, false, false);
		}
	}
}

MazeGrid::~MazeGrid()
{
}

MazeGrid::MazeGrid(const MazeGrid &m)
{
	_width = m._width;
	_height = m._height;

	_grid = m._grid;
}


MazeGrid& MazeGrid::operator=(const MazeGrid &m)
{
	if(this == &m)
		return *this;
	else
	{
		try
		{
			//exceptions
			if(m._width != _width || m._height != _height)
				throw std::invalid_argument("MazeGrids must have the same dimensions");
	
			_grid = m._grid;

			return *this;
		}
		catch(const std::invalid_argument &e)
		{
			std::cerr << e.what() << std::endl;
			return const_cast<MazeGrid&>(m); 
			// here const_cast is allowed because when calling operator= , the left side MazeGrid variable is not a const reference
		}
	}
}

void MazeGrid::carve(const CellCoord src, const CellCoord dest)
{
	try
	{
		const int srcRow = src.first;
		const int srcCol = src.second;

		const int destRow = dest.first;
		const int destCol = dest.second;

		const bool carvingHorizontally = (srcCol != destCol);
		const bool carvingVertically = (srcRow != destRow);

		//exception
		if(carvingHorizontally && carvingVertically)
			throw std::invalid_argument("Cells must be connected for carving");


		CarvingDirection direction; // enum in Mazegrid.hpp

		// determining which walls have to be removed
		if(carvingHorizontally)
		{
			//carving to the left
			if(srcCol < destCol)
				direction = CARVING_EAST;
			else
				direction = CARVING_WEST;

		}
		else
		{

			//carving to the left
			if(srcRow < destRow)
				direction = CARVING_SOUTH;
			else
				direction = CARVING_NORTH;

		}
		
		// removing the corresponding wall
		switch(direction)
		{
			case CARVING_NORTH :
				_grid[src].setNorthWall(false);
				_grid[dest].setSouthWall(false);
				break;
			case CARVING_SOUTH :
				_grid[src].setSouthWall(false);
				_grid[dest].setNorthWall(false);
				break;
			case CARVING_WEST :
				_grid[src].setWestWall(false);
				_grid[dest].setEastWall(false);
				break;
			case CARVING_EAST :
				_grid[src].setEastWall(false);
				_grid[dest].setWestWall(false);
				break;
		}
	}
	catch(const std::invalid_argument &e)
	{
		std::cout << e.what() << std::endl;
	}
}

CellCoord MazeGrid::chooseRandomNeighbors(const CellCoord currentCell)
{
	const int row = currentCell.first;
	const int col = currentCell.second;

	std::uniform_int_distribution<int> intDistribution(1, 4);
	bool correctCell = false;
	CellCoord cell;
	
	while(!correctCell)
	{
		// randomly choosing a neighbor among the four potentially available
		int neighbor = intDistribution(_randomEngine);

		switch(neighbor)
		{
			case 1 :
				//choosing north
				cell = std::make_pair(row-1, col);
				break;
			case 2 :
				//choosing west
				cell = std::make_pair(row, col-1);
				break;
			case 3 :
				//choosing south
				cell = std::make_pair(row+1, col);
				break;
			case 4 :
				//choosing east
				cell = std::make_pair(row, col+1);
				break;
		}

		// checking if the neighbor belongs to the grid
		const bool correctRow = cell.first >= 0 && cell.first < _height;
		const bool correctHeight = cell.second >= 0 && cell.second < _width;

		if(correctRow && correctHeight)
			correctCell = true;
		// else loop again to choose another one
	}

	return cell;
}

std::vector<CellCoord> MazeGrid::getNeighbors(CellCoord cell)
{
	std::vector<CellCoord> neighbor;

	const int row = cell.first;
	const int col = cell.second;

	if(row-1 > 0)
		neighbor.push_back(std::make_pair(row-1, col));
	if(row+1 < _height)
		neighbor.push_back(std::make_pair(row+1, col));
	if(col-1 > 0)
		neighbor.push_back(std::make_pair(row, col-1));
	if(col+1 < _width)
		neighbor.push_back(std::make_pair(row, col+1));

	return neighbor;
}

bool MazeGrid::isDeadEnd(std::pair<int ,int> cell)
{
	auto neighbor = getNeighbors(cell);
	bool unvisitedCell = false;

	const auto neighborEnd = neighbor.end();
	auto it = neighbor.begin();

	// checking if this cell has an unvisited neighbor
	do
	{
		const int row = it->first;
		const int col = it->second;

		if(getCell(row, col).isVisited() == false)
			unvisitedCell = true;

		++it;
	}while(!unvisitedCell && it != neighborEnd);

	if(unvisitedCell)
		return false;
	else
		return true;

}

std::tuple<bool, CellCoord> MazeGrid::hasVisitedNeighbor(const CellCoord cell)
{
	bool visitedNeighbor = false;
	CellCoord validNeighbor;

	auto neighbor = getNeighbors(cell);

	auto neighborEnd = neighbor.end();
	auto it = neighbor.begin();

	while(!visitedNeighbor && it != neighborEnd)
	{
		if(getCell(it->first, it->second).isVisited() == true)
		{
			validNeighbor = *it;
			visitedNeighbor = true;
		}

		++it;
	}

	return std::make_tuple(visitedNeighbor, validNeighbor);
}

bool MazeGrid::isEmpty() const
{
	if(_grid.size() == 0)
		return true;
	else
		return false;
}

void MazeGrid::setVisited(const CellCoord cell)
{
	_grid[cell].setVisited(true);
}

Cell MazeGrid::getCell(const int row, const int col)
{
	return _grid[std::make_pair(row, col)];
}

Cell MazeGrid::getCell(const CellCoord cell)
{
	return _grid[cell];
}