#include "MazeApplication.hpp"

MazeApplication::MazeApplication() : _mainWindow()
{
	//TODO
	/*
		_maze doit etre init avec les valeurs de _mainWindow (mettre getters dans MainWindow)
		ajouter facades de la vue et de l'engine en attributs 
	*/
}

MazeApplication::~MazeApplication()
{

}

void MazeApplication::launch()
{
	_mainWindow.show();
} 