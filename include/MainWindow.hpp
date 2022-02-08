#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QGraphicsScene>
#include <QMainWindow>
#include <QPainter>
#include <QWidget>

#include <utility>

#include "EngineFacade.hpp"
#include "MazeGraphicsItem.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    Ui::MainWindow* ui;
    QGraphicsScene* _scene;
    MazeGraphicsItem* _mazeItem;

    EngineFacade* _engine;

    std::default_random_engine _randomIntGenerator;

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

    std::pair<int, int> getMazeSize();

public slots:
    void generate();
};

#endif
