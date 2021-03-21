#include "Maze.hpp"

#include <iostream>

Maze::Maze()
{
	_grid = nullptr;

	_width = 0;
	_height = 0;
}

Maze::Maze(int width, int height)
{
	_width = width;
	_height = height;

	_grid = new Cell*[height];

	for (int row = 0; row < height; ++row)
	{
		_grid[row] = new Cell[width];
	}
}

Maze::Maze(int width, int height, std::pair<int, int> entryPos, std::pair<int, int> exitPos, bool allWallsBuilt)
{
	_width = width;
	_height = height;

	_grid = new Cell*[height];

	for (int row = 0; row < height; ++row)
	{
		_grid[row] = new Cell[width];

		for (int col = 0; col < width; ++col)
		{
			if(entryPos.first == row && entryPos.second == col) // cell is entry
				_grid[row][col] = Cell(row, col, false, true, false);
			
			else if(exitPos.first == row && exitPos.second == col)// cell is exit
				_grid[row][col] = Cell(row, col, false, false, true);
			
			else // cell is a normal cell
				_grid[row][col] = Cell(row, col, allWallsBuilt, false, false);
		}
	}
}

Maze::~Maze()
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

Maze::Maze(const Maze &m)
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

Maze& Maze::operator=(const Maze &m)
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
			std::cerr << "Mazes have to be the same size" << std::endl; // TODO : add an exception later
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

Cell Maze::getCell(int row, int col) const
{
	return _grid[row][col];
}

void Maze::setCellWalls(int row, int col, bool north, bool west, bool south, bool east)
{
	_grid[row][col].setWalls(north, west, south, east);
}

int Maze::carve(std::pair<int, int> src, std::pair<int, int> dest)
{
	// determining which walls to be removed

	int srcRow = src.first;
	int srcCol = src.second;

	int destRow = dest.first;
	int destCol = dest.second;

	CarvingDirection direction;

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

void Maze::huntAndKill()
{
	carve(std::make_pair(2, 2), std::make_pair(2, 3));
	carve(std::make_pair(2, 2), std::make_pair(2, 1));
	carve(std::make_pair(2, 2), std::make_pair(1, 2));
	carve(std::make_pair(2, 2), std::make_pair(3, 2));
}