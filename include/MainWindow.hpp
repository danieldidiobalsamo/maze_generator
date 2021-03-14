#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QWidget>
#include <QGraphicsScene>
#include <QPainter>

#include "WallWidget.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

	private:
	    Ui::MainWindow *ui;
	    QGraphicsScene *_scene;
	    WallWidget *w;

	public:
	    explicit MainWindow(QWidget *parent = 0);
	    ~MainWindow();
};

#endif
