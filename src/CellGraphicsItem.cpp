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
	return _rect;
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

void CellGraphicsItem::generate(float x, float y, float w, float h, const Cell &cell)
{
	_rect = QRectF(x, y, w, h);

	QBrush blackBrush(Qt::black);
	QPen blackPen(Qt::black);
	blackPen.setWidth(1);

	_northWall = new WallGraphicsItem(x-2.0f, y-2.0f, w+2.0f, 2.0f, blackPen, blackBrush);
	_westWall = new WallGraphicsItem(x-2.0f, y-1, 2.0f, h+1, blackPen, blackBrush);
	_southWall = new WallGraphicsItem(x-2.0f, y+h, w+2.0f, 2.0f, blackPen, blackBrush);
	_eastWall = new WallGraphicsItem(x+w, y-1, 2.0f, h+1, blackPen, blackBrush);

	Walls walls = cell.getWalls();

	buildWalls(walls);
}
//////////////////////////////////////////////////////////////////