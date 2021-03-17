#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "Maze.hpp"
#include "MainWindow.hpp"

class MazeApplication
{
	private :
		MainWindow _mainWindow;
		Maze _maze;

	public :

		MazeApplication();
		~MazeApplication();

		void launch();
};

#endif