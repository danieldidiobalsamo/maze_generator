#include <QApplication>
#include "MainWindow.hpp"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	MainWindow window;
	window.show();
	window.generate();//tmp : dans le futur c'est une méthode appeler via l'event click du bouton associé

	return app.exec();
}