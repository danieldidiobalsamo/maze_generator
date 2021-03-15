#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QWidget>
#include <QGraphicsScene>
#include <QPainter>

#include "WallGraphicsItem.hpp"
#include "CellGraphicsItem.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

	private:
	    Ui::MainWindow *ui;
	    QGraphicsScene *_scene;
	    WallGraphicsItem *_w;
	    CellGraphicsItem *_c;

	public:
	    explicit MainWindow(QWidget *parent = 0);
	    ~MainWindow();
};

#endif