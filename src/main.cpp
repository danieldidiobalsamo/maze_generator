#include <iostream>

#include <QApplication>
#include <QWidget>

#include "Maze.hpp"

#include "MainWindow.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	Maze m(5, 5);

	QApplication app(argc, argv);
	MainWindow window;

	window.show();

	return app.exec();
}