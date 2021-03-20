#include "Walls.hpp"

#include <iostream>

Walls::Walls()
{
	_westWall = true;
	_eastWall = true;
	_northWall = true;
	_southWall = true;
}

Walls::Walls(bool built)
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
void Walls::setWestWall(bool built)
{
	_westWall = built;
}
void Walls::setEastWall(bool built)
{
	_eastWall = built;
}
void Walls::setNorthWall(bool built)
{
	_northWall = built;
}
void Walls::setSouthWall(bool built)
{
	_southWall = built;
}

// method to print the walls in the terminal
void Walls::printWalls()
{
	std::cout << "West wall : " << _westWall << std::endl;
	std::cout << "North wall : " << _northWall << std::endl;
	std::cout << "East wall : " << _eastWall << std::endl;
	std::cout << "South wall : " << _southWall << std::endl;
}