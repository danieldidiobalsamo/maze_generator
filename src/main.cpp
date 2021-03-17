#include <QApplication>
#include "MazeApplication.hpp"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	MazeApplication mazeAppli;
	mazeAppli.launch();

	return app.exec();
}