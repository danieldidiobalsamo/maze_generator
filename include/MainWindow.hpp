#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QWidget>
#include <QGraphicsScene>
#include <QPainter>

#include <utility>

#include "MazeGraphicsItem.hpp"
#include "EngineFacade.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

	private:
	    Ui::MainWindow *ui;
	    QGraphicsScene *_scene;
	    MazeGraphicsItem *_mazeItem;

	    EngineFacade *_engine;

	    std::default_random_engine _randomIntGenerator;

	public:
	    explicit MainWindow(QWidget *parent = 0);
	    ~MainWindow();

	    std::pair<int, int> getMazeSize();

	public slots:
	    void generate();
};

#endif
