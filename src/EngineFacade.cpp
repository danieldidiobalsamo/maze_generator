#include "EngineFacade.hpp"

EngineFacade::EngineFacade()
{
	_mazeWidth = 0;
	_mazeHeight = 0;
}

EngineFacade::EngineFacade(int w, int h, std::pair<int, int> entryPos, std::pair<int, int> exitPos, bool allWallsBuilt) : _mazeWidth(w), _mazeHeight(h), _maze(w, h, allWallsBuilt, entryPos, exitPos)
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