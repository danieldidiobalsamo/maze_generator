#include "MainWindow.hpp"
#include "ui_MainWindow.h" // automatically generated

#include "MazeGraphicsItem.hpp"

#include <QBrush>
#include <QPen>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
	_scene = new QGraphicsScene(this);

	/*_mazeItem = new MazeGraphicsItem(20, 20, 30, 30);
	_scene->addItem(_mazeItem);

    ui->mazeGraphicsView->setScene(_scene);*/

    QObject::connect(ui->exitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
}

MainWindow::~MainWindow()
{
    //_scene->removeItem(_w);
	//_scene->removeItem(_c);
	//_scene->removeItem(_mazeItem);
 
	if(_mazeItem != nullptr)
	{
    	_scene->destroyItemGroup(_mazeItem);
	}

    delete ui;
    delete _scene;


    //delete _mazeItem;

   /* delete _w;
    delete _c;*/
}

std::pair<int, int> MainWindow::getMazeSize()
{
	return std::make_pair(ui->widthSpinBox->value(), ui->heightSpinBox->value());
}

void MainWindow::generate()
{
	// generating the maze

	std::pair<int, int> mazeSize = getMazeSize();
	//todo : genérer random départ et exit selon le côté choisi
	_engine = EngineFacade(mazeSize.first, mazeSize.second, std::make_pair(0,5), std::make_pair(19, 19), true);
	_engine.generateMaze("hunt");

	//drawing the maze

	_mazeItem = new MazeGraphicsItem(20, 20, 30, 30, _engine.getMaze());
	_scene->addItem(_mazeItem);

    ui->mazeGraphicsView->setScene(_scene);

}