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

Maze::Maze(int width, int height, bool allWallsBuilt, std::pair<int, int> entryPos, std::pair<int, int> exitPos)
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