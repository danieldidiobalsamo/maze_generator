#include "MazeGrid.hpp"

#include <iostream>

MazeGrid::MazeGrid() : _randomEngine(static_cast<unsigned int>(time(0))) // used to generate random int, better than rand()
{
	_grid = nullptr;

	_width = 0;
	_height = 0;
}

MazeGrid::MazeGrid(int width, int height) : _randomEngine(static_cast<unsigned int>(time(0))) // used to generate random int, better than rand()
{
	_width = width;
	_height = height;

	_grid = new Cell*[height];

	for (int row = 0; row < height; ++row)
	{
		_grid[row] = new Cell[width];
	}
}

MazeGrid::MazeGrid(int width, int height, std::pair<int, int> entryPos, std::pair<int, int> exitPos, bool allWallsBuilt) : _randomEngine(static_cast<unsigned int>(time(0))) // used to generate random int, better than rand()
{
	_width = width;
	_height = height;

	_entryPos = entryPos;
	_exitPos = exitPos;

	_grid = new Cell*[height];

	for (int row = 0; row < height; ++row)
	{
		_grid[row] = new Cell[width];

		// determining if the cell is an entry, exit or normal cell
		for (int col = 0; col < width; ++col)
		{
			if(entryPos.first == row && entryPos.second == col) // cell is entry
				_grid[row][col] = Cell(row, col, false, true, false);
			
			else if(exitPos.first == row && exitPos.second == col)// cell is exit
			{
				_grid[row][col] = Cell(row, col, false, false, true);
			}
			
			else // cell is a normal cell
				_grid[row][col] = Cell(row, col, allWallsBuilt, false, false);
		}
	}
}

MazeGrid::~MazeGrid()
{
	if(_grid != nullptr)
	{
		for (int row = 0; row < _height; ++row)
		{
			delete[] _grid[row];
		}

		delete[] _grid;
	}
}

MazeGrid::MazeGrid(const MazeGrid &m)
{
	_width = m._width;
	_height = m._height;

	// allocation of the maze

	_grid = new Cell*[_height];

	for (int row = 0; row < _height; ++row)
	{
		_grid[row] = new Cell[_width];
	}

	// copy of the original maze
	for (int row = 0; row < _height; ++row)
	{
		for (int col = 0; col < _width; ++col)
		{
			_grid[row][col] = m._grid[row][col];
		}
	}
}


MazeGrid& MazeGrid::operator=(const MazeGrid &m)
{
	if(this == &m)
		return *this;
	else
	{
		if(this->_grid == nullptr)
		{
			_width = m._width;
			_height = m._height;

			// allocation of the maze

			_grid = new Cell*[_height];

			for (int row = 0; row < _height; ++row)
			{
				_grid[row] = new Cell[_width];
			}

			// copy of the original maze
			for (int row = 0; row < _height; ++row)
			{
				for (int col = 0; col < _width; ++col)
				{
					_grid[row][col] = m._grid[row][col];
				}
			}

			return *this;
		}
		else if(m._width != _width || m._height != _height)
		{
			std::cout << "Mazes must have the same size" << std::endl; // TODO : add an exception later
			return *this;
		}
		else
		{
			// copy of the original maze
			for (int row = 0; row < _height; ++row)
			{
				for (int col = 0; col < _width; ++col)
				{
					_grid[row][col] = m._grid[row][col];
				}
			}

			return *this;
		}
	}
}

int MazeGrid::carve(std::pair<int, int> src, std::pair<int, int> dest)
{

	int srcRow = src.first;
	int srcCol = src.second;

	int destRow = dest.first;
	int destCol = dest.second;

	CarvingDirection direction; // enum in Mazegrid.hpp

	// determining which walls have to be removed
	if(srcCol != destCol) //carving horizontally
	{
		//carving to the left
		if(srcCol < destCol)
			direction = CARVING_EAST;
		else
			direction = CARVING_WEST;

	}
	else if(srcRow != destRow) //carving vertically
	{

		//carving to the left
		if(srcRow < destRow)
			direction = CARVING_SOUTH;
		else
			direction = CARVING_NORTH;

	}
	else
	{
		// TODO : refactor en utilisant des exceptions
		std::cout << "Cells are not connected" << std::endl;
		return -1;
	}

	
	// removing the corresponding wall
	switch(direction)
	{
		case CARVING_NORTH :
			_grid[srcRow][srcCol].setNorthWall(false);
			_grid[destRow][destCol].setSouthWall(false);
			break;
		case CARVING_SOUTH :
			_grid[srcRow][srcCol].setSouthWall(false);
			_grid[destRow][destCol].setNorthWall(false);
			break;
		case CARVING_WEST :
			_grid[srcRow][srcCol].setWestWall(false);
			_grid[destRow][destCol].setEastWall(false);
			break;
		case CARVING_EAST :
			_grid[srcRow][srcCol].setEastWall(false);
			_grid[destRow][destCol].setWestWall(false);
			break;
	}

	return 0;
}

std::pair<int, int> MazeGrid::chooseRandomNeighbors(int row, int col)
{
	std::uniform_int_distribution<int> intDistribution(1, 4);
	bool correctCell = false;
	std::pair<int, int> cell;

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
		bool correctRow = cell.first >= 0 && cell.first < _height;
		bool correctHeight = cell.second >= 0 && cell.second < _width;

		if(correctRow && correctHeight)
			correctCell = true;
		// else loop again to choose another one
	}

	return cell;
}

std::vector<std::pair<int, int>> MazeGrid::getNeighbors(std::pair<int, int> cell)
{
	std::vector<std::pair<int, int>> neighbor;

	int row = cell.first;
	int col = cell.second;

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
	std::vector<std::pair<int, int>> neighbor = getNeighbors(cell);
	bool unvisitedCell = false;

	std::vector<std::pair<int, int>>::iterator neighborEnd = neighbor.end();
	std::vector<std::pair<int, int>>::iterator it = neighbor.begin();

	// checking if this cell has an unvisited neighbor
	do
	{
		int row = it->first;
		int col = it->second;

		if(_grid[row][col].isVisited() == false)
			unvisitedCell = true;

		++it;
	}while(!unvisitedCell && it != neighborEnd);

	if(unvisitedCell)
		return false;
	else
		return true;

}

bool MazeGrid::hasVisitedNeighbor(std::pair<int, int> cell, std::pair<int, int> &validNeighbor)
{
	bool visitedNeighbor = false;

	std::vector<std::pair<int, int>> neighbor = getNeighbors(std::make_pair(cell.first, cell.second));

	std::vector<std::pair<int, int>>::iterator neighborEnd = neighbor.end();
	std::vector<std::pair<int, int>>::iterator it = neighbor.begin();

	while(!visitedNeighbor && it != neighborEnd)
	{
		if(_grid[it->first][it->second].isVisited() == true)
		{
			validNeighbor = *it;
			visitedNeighbor = true;
		}

		++it;
	}

	return visitedNeighbor;
}

bool MazeGrid::isEmpty()
{
	if(_grid == nullptr)
		return true;
	else
		return false;
}

Cell& MazeGrid::getCell(int row, int col) const
{
	return _grid[row][col];
}