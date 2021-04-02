#include "WallGraphicsItem.hpp"
#include <iostream>

//////////////////////////////////////////////////////////////////
// constructors
WallGraphicsItem::WallGraphicsItem() : _rect(), _pen(), _brush()
{
}

WallGraphicsItem::WallGraphicsItem(float x, float y, float w, float h, QPen &pen, QBrush &brush) : _rect(x, y, w, h), _pen(pen), _brush(brush)
{

}

WallGraphicsItem::~WallGraphicsItem()
{

}

//////////////////////////////////////////////////////////////////
// implements virtual pure function from QGraphicsItem

QRectF WallGraphicsItem::boundingRect() const
{
	return _rect;
}

void WallGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	Q_UNUSED(option);
	Q_UNUSED(widget);

    painter->setBrush(_brush);
    painter->setPen(_pen);
    painter->drawRect(_rect);
}
//////////////////////////////////////////////////////////////////