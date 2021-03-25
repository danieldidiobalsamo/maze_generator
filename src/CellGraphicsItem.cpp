#include "CellGraphicsItem.hpp"
#include "Cell.hpp"

#include <iostream>
#include <cmath>

//////////////////////////////////////////////////////////////////
// constructors
CellGraphicsItem::CellGraphicsItem() : _rect(), _pen(Qt::lightGray, 2), _brush(Qt::lightGray)
{
	_northWall = nullptr;
	_westWall = nullptr;
	_southWall = nullptr;
	_eastWall = nullptr;
}

CellGraphicsItem::~CellGraphicsItem()
{
	if(_northWall != nullptr)
	{
		delete _northWall;
	}
	if(_westWall != nullptr)
	{
		delete _westWall;
	}
	if(_southWall != nullptr)
	{
		delete _southWall;
	}
	if(_eastWall != nullptr)
	{
		delete _eastWall;
	}
}
//////////////////////////////////////////////////////////////////
// implements virtual pure function from QGraphicsItem

QRectF CellGraphicsItem::boundingRect() const
{
	return QRectF(_rect);
}

void CellGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	Q_UNUSED(option);
	Q_UNUSED(widget);

    //QPen pen(Qt::black, 3);
    painter->setBrush(_brush);
    painter->setPen(_pen);
    painter->drawRect(_rect);
}

void CellGraphicsItem::setRect(QRect rect)
{
	_rect = rect;
}

void CellGraphicsItem::buildWalls(Walls &walls)
{
	if(walls.hasNorthWall())
	{
		addToGroup(_northWall);
	}
	if(walls.hasWestWall())
	{
		addToGroup(_westWall);
	}
	if(walls.hasEastWall())
	{
		addToGroup(_eastWall);
	}
	if(walls.hasSouthWall())
	{
		addToGroup(_southWall);
	}
}

void CellGraphicsItem::generate(int x, int y, int w, int h, const Cell &cell)
{
	_rect = QRect(x, y, w, h);

	QBrush blackBrush(Qt::black);
	QPen blackPen(Qt::black);
	blackPen.setWidth(1);

	_northWall = new WallGraphicsItem(x, y-floor(h/4), w, 10, blackPen, blackBrush);
	_westWall = new WallGraphicsItem(x-floor(w/4), y, 10, h, blackPen, blackBrush);
	_southWall = new WallGraphicsItem(x, y+floor(h*0.95), w, 10, blackPen, blackBrush);
	_eastWall = new WallGraphicsItem(x+floor(w*0.95), y, 10, h, blackPen, blackBrush);

	Walls walls = cell.getWalls();

	buildWalls(walls);
}
//////////////////////////////////////////////////////////////////