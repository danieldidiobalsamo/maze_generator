#ifndef WALL_WIDGET_HPP
#define WALL_WIDGET_HPP

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPaintEvent>
#include <QPainter>
#include <QRect>
#include <QRectF>

class WallGraphicsItem : public QGraphicsItem {
private:
    QRectF _rect;
    QPen _pen;
    QBrush _brush;

public:
    WallGraphicsItem();
    WallGraphicsItem(float x, float y, float w, float h, QPen& pen, QBrush& brush);
    ~WallGraphicsItem();

    // implements virtual pure function from QGraphicsItem
    QRectF boundingRect() const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
};

#endif