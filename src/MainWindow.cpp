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
//tmp
	QBrush blackBrush(Qt::black);
	QPen pen(Qt::black);
	pen.setWidth(2);
	_w = new WallGraphicsItem(0, 0, 40, 10, pen, blackBrush);

	QBrush yellowBrush(Qt::yellow);
	QPen yellowPen(Qt::yellow);
	pen.setWidth(2);

	_c = new CellGraphicsItem(50, 50, 30, 30, yellowPen, yellowBrush);

	_scene->addItem(_w);
	_scene->addItem(_c);

    ui->mazeGraphicsView->setScene(_scene);

    //QObject::connect(ui->exitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
    QObject::connect(ui->exitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
}

MainWindow::~MainWindow()
{
    _scene->removeItem(_w);
	_scene->removeItem(_c);

    delete ui;
    delete _scene;

    delete _w;
    delete _c;
}