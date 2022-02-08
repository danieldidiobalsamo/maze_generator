#ifndef CELL_WIDGET_HPP
#define CELL_WIDGET_HPP

#include <QGraphicsItemGroup>
#include <QGraphicsScene>
#include <QPaintEvent>
#include <QPainter>
#include <QRect>
#include <QRectF>
#include <vector>

#include "Cell.hpp"
#include "WallGraphicsItem.hpp"

class CellGraphicsItem : public QGraphicsItemGroup {
private:
    QRectF _rect;
    QPen _pen;
    QBrush _brush;

    // walls that can be built
    WallGraphicsItem* _northWall;
    WallGraphicsItem* _westWall;
    WallGraphicsItem* _southWall;
    WallGraphicsItem* _eastWall;

    void buildWalls(Walls& walls);

public:
    CellGraphicsItem();
    ~CellGraphicsItem();

    // implements virtual pure function from QGraphicsItem
    QRectF boundingRect() const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

    void generate(float x, float y, float w, float h, const Cell& cell);
};

#endif