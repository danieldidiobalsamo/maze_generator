#include "Walls.hpp"

#include <iostream>

Walls::Walls()
{
	_westWall = true;
	_eastWall = true;
	_northWall = true;
	_southWall = true;
}

Walls::Walls(const bool built)
{
	_westWall = built;
	_eastWall = built;
	_northWall = built;
	_southWall = built;
}

Walls::~Walls()
{

}


// methods to tests if walls exist
bool Walls::hasWestWall()
{
	return _westWall;
}
bool Walls::hasEastWall()
{
	return _eastWall;
}
bool Walls::hasNorthWall()
{
	return _northWall;
}
bool Walls::hasSouthWall()
{
	return _southWall;
}

// methods to build walls
void Walls::setWestWall(const bool built)
{
	_westWall = built;
}
void Walls::setEastWall(const bool built)
{
	_eastWall = built;
}
void Walls::setNorthWall(const bool built)
{
	_northWall = built;
}
void Walls::setSouthWall(const bool built)
{
	_southWall = built;
}