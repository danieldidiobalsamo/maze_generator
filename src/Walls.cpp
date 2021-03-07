#include "Walls.hpp"

#include <iostream>

Walls::Walls()
{
	_westWall = false;
	_eastWall = false;
	_northWall = false;
	_southWall = false;
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
void Walls::buildWestWall()
{
	_westWall = true;
}
void Walls::buildEastWall()
{
	_eastWall = true;
}
void Walls::buildNorthWall()
{
	_northWall = true;
}
void Walls::buildSouthWall()
{
	_southWall = true;
}


// methods to remove walls
void Walls::removeWestWall()
{
	_westWall = false;
}
void Walls::removeEastWall()
{
	_eastWall = false;
}
void Walls::removeNorthWall()
{
	_northWall = false;
}
void Walls::removeSouthWall()
{
	_southWall = false;
}


// method to print the walls in the terminal
void Walls::printWalls()
{
	std::cout << "West wall : " << _westWall << std::endl;
	std::cout << "North wall : " << _northWall << std::endl;
	std::cout << "East wall : " << _eastWall << std::endl;
	std::cout << "South wall : " << _southWall << std::endl;
}