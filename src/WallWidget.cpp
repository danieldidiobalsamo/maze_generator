#include "WallWidget.hpp"
#include <iostream>

//////////////////////////////////////////////////////////////////
// constructors
WallWidget::WallWidget() : _rect(), _pen(), _brush()
{
}

WallWidget::WallWidget(int x, int y, int w, int h, QPen &pen, QBrush &brush) : _rect(x, y, w, h), _pen(pen), _brush(brush)
{

}

WallWidget::~WallWidget()
{

}

//////////////////////////////////////////////////////////////////
// implements virtual pure function from QGraphicsItem

QRectF WallWidget::boundingRect() const
{
	return QRectF(_rect);
}

void WallWidget::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	Q_UNUSED(option);
	Q_UNUSED(widget);

    //QPen pen(Qt::black, 3);
    painter->setBrush(_brush);
    painter->setPen(_pen);
    painter->drawRect(_rect);
}
//////////////////////////////////////////////////////////////////