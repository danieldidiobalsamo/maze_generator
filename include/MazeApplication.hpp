#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "EngineFacade.hpp"
#include "MainWindow.hpp"

#include <utility>

class MazeApplication
{
	private :
		MainWindow _mainWindow;
		EngineFacade _engine;

	public :

		MazeApplication();
		~MazeApplication();

		void launch();
		void generate();
};

#endif