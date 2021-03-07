#include "Cell.hpp"

////////////////////////////
// Coplien

Cell::Cell() : _x(0), _y(0), _visited(false), _walls()
{

}

Cell::Cell(int x, int y, bool built) : _x(x), _y(y), _visited(false), _walls(built)
{
	
}

Cell::Cell(const Cell &c)
{
	_x = c._x;
	_y = c._y;

	_visited = c._visited;
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
		_x = c._x;
		_y = c._y;
		_visited = c._visited;
		_walls = c._walls;

		return *this;
	}
}

////////////////////////////