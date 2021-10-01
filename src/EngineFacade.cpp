#include "EngineFacade.hpp"

#include <iostream>

EngineFacade::EngineFacade()
{
	_mazeWidth = 0;
	_mazeHeight = 0;
}

EngineFacade::EngineFacade(const int w, const int h, const CellCoord entryPos, const CellCoord exitPos, const bool allWallsBuilt) : _mazeWidth(w), _mazeHeight(h), _maze(w, h, entryPos, exitPos, allWallsBuilt)
{

}

EngineFacade::~EngineFacade()
{

}

EngineFacade& EngineFacade::operator=(const EngineFacade &f)
{
	if(this == &f)
		return *this;
	else
	{
		_mazeWidth = f._mazeWidth;
		_mazeHeight = f._mazeHeight;

		_entryPos = f._entryPos;
		_exitPos = f._exitPos;

		_maze = f._maze;

		return *this;
	}	
}

void EngineFacade::generateMaze(const std::string algo)
{
	if(algo == "Hunt and kill")
		huntAndKillGeneration();
	else
	{
		std::cout << "Bad algorithm name : " << algo << std::endl;
	}
}

void EngineFacade::huntAndKillGeneration()
{
	_maze.huntAndKill();
}

Maze& EngineFacade::getMaze()
{
	return _maze;
}