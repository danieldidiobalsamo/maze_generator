#include "Maze.hpp"

#include <iostream>
#include <stdexcept>

Maze::Maze() : _grid()
{
	_width = 0;
	_height = 0;
}

Maze::Maze(int width, int height) : _grid(width, height)
{
	_width = width;
	_height = height;
}

Maze::Maze(int width, int height, std::pair<int, int> entryPos, std::pair<int, int> exitPos, bool allWallsBuilt):
_grid(width, height, entryPos, exitPos, allWallsBuilt)
{
	_width = width;
	_height = height;

	_entryPos = entryPos;
	_exitPos = exitPos;
}

Maze::~Maze()
{
}

Maze::Maze(const Maze &m)
{
	_width = m._width;
	_height = m._height;

	// allocation of the maze

	_grid = m._grid; // Mazegrid's operator= is overloaded
}

Maze& Maze::operator=(const Maze &m)
{
	if(this == &m)
		return *this;
	else
	{
		try
		{
			// managing exceptions
			if(m.isEmpty())
				throw std::invalid_argument("Maze is empty");
			else
			{
				if(m._width != _width || m._height != _height)
					throw std::invalid_argument("Mazes dimensions must be the same");
			}

			// copying the maze
			_width = m._width;
			_height = m._height;

			_grid = m._grid;

			return *this;
		}
		catch(const std::invalid_argument &e)
		{
			std::cerr << e.what() << std::endl;
			return const_cast<Maze&>(m); 
			// here const_cast is allowed because when calling operator= , the left side Maze variable is not a const reference
		}
	}
}

bool Maze::isEmpty() const
{
	return _grid.isEmpty();
}

Cell Maze::getCell(int row, int col)
{
	return _grid.getCell(row, col);
}

void Maze::visitCell(std::pair<int, int> cell)
{
	_grid.setVisited(cell);
}

void Maze::huntAndKill()
{
	std::pair<int, int> currentCell = _entryPos;

	visitCell(currentCell);
	
	std::pair<int, int> nextCell;
	bool allCellsTreated = false;
	bool huntMode = false;


	//looping on the whole maze
	do
	{
		do // looping until a dead end is reached
		{
			if(_grid.isDeadEnd(currentCell))
			{
				// launching hunt mode
				huntMode = true;
			}
			else
			{
				//choosing an unvisited cell

				do
				{
					nextCell = _grid.chooseRandomNeighbors(currentCell);
				}while(_grid.getCell(nextCell.first, nextCell.second).isVisited());

				visitCell(nextCell);
				_grid.carve(currentCell, nextCell);

				currentCell = nextCell;
			}

		}while(!huntMode);

		// hunt mode
		// consists in searching for an unvisited cell which have at least a visited one
		// and searching row by row

		bool selectedCell = false;
		int row = 0, col = 0;

		while(row < _height && !selectedCell)
		{
			col = 0;

			while(col < _width && !selectedCell)
			{	
				if(_grid.getCell(row ,col).isVisited() == false)
				{
					// checking if among its neighbors, there is one who is visited

					std::pair<int, int> neighbor;

					if(_grid.hasVisitedNeighbor(std::make_pair(row, col), neighbor))
					{
						currentCell = std::make_pair(row, col);
						
						_grid.carve(currentCell, neighbor);
						visitCell(currentCell);
						selectedCell = true;
					}
				}
				++col;
			}

			++row;
		}

		if(!selectedCell)
		{
			allCellsTreated = true;
		}
		
		huntMode = false;
	}while(!allCellsTreated);
}