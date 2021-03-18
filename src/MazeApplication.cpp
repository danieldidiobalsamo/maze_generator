#include "MazeApplication.hpp"

#include <iostream>

//////////////tmp
MazeApplication::MazeApplication() : _mainWindow(), _engine(20, 20, std::make_pair(0,0), std::make_pair(19, 19), true) //tmp
{

}

MazeApplication::~MazeApplication()
{

}

void MazeApplication::launch()
{
	_mainWindow.show();
}

void MazeApplication::generate()
{
//tmp : should be called by MainWindow via "generate" button

	std::pair<int, int> mazeSize = _mainWindow.getMazeSize();
	_engine = EngineFacade(mazeSize.first, mazeSize.second, std::make_pair(0,0), std::make_pair(19, 19), true);
}