#include "MainWindow.hpp"
#include "ui_MainWindow.h" // automatically generated

#include "MazeGraphicsItem.hpp"

#include <QBrush>
#include <QPen>
#include <QPainter>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _randomIntGenerator(static_cast<unsigned int>(time(0)))
{
	_engine = nullptr;
	_mazeItem = nullptr;

    ui->setupUi(this);
	_scene = new QGraphicsScene(this);

    QObject::connect(ui->exitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
    QObject::connect(ui->generateButton, SIGNAL(clicked()), this, SLOT(generate()));
}

MainWindow::~MainWindow()
{
	if(_mazeItem != nullptr)
	{
		delete _mazeItem;
	}

	if(_engine != nullptr)
	{
		delete _engine;
	}

    delete _scene;
    delete ui;
}

std::pair<int, int> MainWindow::getMazeSize()
{
	return std::make_pair(ui->widthSpinBox->value(), ui->heightSpinBox->value());
}

void MainWindow::generate()
{
	// generating the maze

	std::pair<int, int> mazeSize = getMazeSize();

	// determining random entry
	//TODO amélioration : selon le côté choisi
	int w = mazeSize.first;
	int h = mazeSize.second;

	std::uniform_int_distribution<int> widthDistrib(0, w-1);

	std::pair<int, int> randomEntry = std::make_pair(0, widthDistrib(_randomIntGenerator));

	if(_engine != nullptr)
		delete _engine;

	_engine = new EngineFacade(mazeSize.first, mazeSize.second, randomEntry, std::make_pair(h-1, w-1), true);
	_engine->generateMaze("hunt");

	//drawing the maze

	if(_mazeItem != nullptr)
		_scene->destroyItemGroup(_mazeItem);

	_mazeItem = new MazeGraphicsItem(w, h, 30, 30, _engine->getMaze());
	_scene->addItem(_mazeItem);

    ui->mazeGraphicsView->setScene(_scene);
}