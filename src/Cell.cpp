#include "Cell.hpp"

////////////////////////////
// Coplien

Cell::Cell() : _row(0), _col(0), _visited(false), _isEntry(false), _isExit(false), _walls()
{

}

Cell::Cell(int row, int col, bool built, bool isEntry, bool isExit) : _row(row), _col(col), _visited(false), _isEntry(isEntry), _isExit(isExit),_walls(built)
{
	
}

Cell::Cell(const Cell &c)
{
	_row = c._row;
	_col = c._col;

	_visited = c._visited;
	_isEntry = c._isEntry;
	_isExit = c._isExit;
	_walls = c._walls;
}

Cell::~Cell()
{

}

Cell& Cell::operator=(const Cell &c)
{
	if(this == &c)
	{
		return *this;
		// (to avoid memory leaks)
	}
	else
	{
		_row = c._row;
		_col = c._col;
		_visited = c._visited;
		_isEntry = c._isEntry;
		_isExit = c._isExit;
		_walls = c._walls;

		return *this;
	}
}

////////////////////////////