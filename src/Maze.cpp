#include "Maze.hpp"

#include <iostream>

Maze::Maze() : _randomEngine(time(0))
{
	_grid = nullptr;

	_width = 0;
	_height = 0;
}

Maze::Maze(int width, int height) : _randomEngine(time(0))
{
	_width = width;
	_height = height;

	_grid = new Cell*[height];

	for (int row = 0; row < height; ++row)
	{
		_grid[row] = new Cell[width];
	}
}

Maze::Maze(int width, int height, std::pair<int, int> entryPos, std::pair<int, int> exitPos, bool allWallsBuilt) : _randomEngine(time(0))
{
	_width = width;
	_height = height;

	_entryPos = entryPos;
	_exitPos = exitPos;

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

std::pair<int, int> Maze::chooseRandomNeighbors(int row, int col)
{
	std::uniform_int_distribution<int> intDistribution(1, 4);

	bool correctCell = false;

	std::pair<int, int> cell;

	while(!correctCell)
	{
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

		bool correctRow = cell.first >= 0 && cell.first < _height;
		bool correctHeight = cell.second >= 0 && cell.second < _width;

		if(correctRow && correctHeight)
			correctCell = true;
	}

	return cell;
}

std::vector<std::pair<int, int>> Maze::getNeighbors(std::pair<int, int> cell)
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

bool Maze::isDeadEnd(std::pair<int ,int> cell)
{
	std::vector<std::pair<int, int>> neighbor = getNeighbors(cell);
	bool unvisitedCell = false;

	std::vector<std::pair<int, int>>::iterator neighborEnd = neighbor.end();
	std::vector<std::pair<int, int>>::iterator it = neighbor.begin();

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

bool Maze::hasVisitedNeighbor(std::pair<int, int> cell, std::pair<int, int> &validNeighbor)
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

void Maze::huntAndKill()
{
	// TODO : ajouter un compteur + getter pour la barre de progression lors de la génération

	std::pair<int, int> currentCell = _entryPos;
	_grid[currentCell.first][currentCell.second].setVisited(true);
	
	std::pair<int, int> nextCell;
	bool allCellsTreated = false;
	bool huntMode = false;


	//looping on the whole maze
	do
	{
		do // looping until a dead end is reached
		{
			if(isDeadEnd(currentCell))
			{
				// launching hunt mode
				huntMode = true;
			}
			else
			{
				//choosing an unvisited cell

				do
				{
					nextCell = chooseRandomNeighbors(currentCell.first, currentCell.second);
				}while(_grid[nextCell.first][nextCell.second].isVisited());

				_grid[nextCell.first][nextCell.second].setVisited(true);
				carve(currentCell, nextCell);

				currentCell = nextCell;
			}

		}while(!huntMode);

		// hunt mode

		bool selectedCell = false;
		int row = 0, col = 0;

		while(row < _height && !selectedCell)
		{
			col = 0;

			while(col < _width && !selectedCell)
			{	
				if(_grid[row][col].isVisited() == false)
				{
					// checking if among its neighbors, there is one who is visited

					std::pair<int, int> neighbor;

					if(hasVisitedNeighbor(std::make_pair(row, col), neighbor))
					{
						currentCell = std::make_pair(row, col);
						carve(currentCell, neighbor);

						_grid[row][col].setVisited(true);
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