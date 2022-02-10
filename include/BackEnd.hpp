#pragma once

#include <QObject>
#include <QString>
#include <qqml.h>
#include <utility>

#include "EngineFacade.hpp"

class BackEnd : public QObject {
    Q_OBJECT

public:
    explicit BackEnd(QObject* parent = nullptr);
    ~BackEnd();

    Q_INVOKABLE void setMazeWidth(int _width);
    Q_INVOKABLE void setMazeHeight(int _height);
    Q_INVOKABLE void setAlgo(QString algo);
    Q_INVOKABLE void generateMaze();
    Q_INVOKABLE QVariantList getCell(int row, int col);

private:
    EngineFacade* _engine;

    int _mazeWidth;
    int _mazeHeight;
    CellCoord _entryPos;
    CellCoord _exitPos;

    QString _algo;

    std::default_random_engine _randomIntGenerator;
};