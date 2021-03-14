#include "MainWindow.hpp"
#include "ui_MainWindow.h" // automatically generated

#include <QBrush>
#include <QPen>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
	_scene = new QGraphicsScene(this);

	QBrush blackBrush(Qt::black);
	QPen pen(Qt::black);
	pen.setWidth(2);
	w = new WallWidget(0, 0, 40, 10, pen, blackBrush);

	_scene->addItem(w);

    ui->mazeGraphicsView->setScene(_scene);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete _scene;
}