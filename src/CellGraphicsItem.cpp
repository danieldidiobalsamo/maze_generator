#include "CellGraphicsItem.hpp"
#include "Cell.hpp"

#include <iostream>
#include <cmath>

//////////////////////////////////////////////////////////////////
// constructors
CellGraphicsItem::CellGraphicsItem() : _rect(), _pen(Qt::lightGray, 2), _brush(Qt::lightGray)
{

}
/*
CellGraphicsItem::CellGraphicsItem(int x, int y, int w, int h, QPen &pen, QBrush &brush, const Cell &cell) : 
_rect(x, y, w, h), 
_pen(pen), 
_brush(brush)
{
	std::cout << "constructor" << std::endl;

	QBrush blackBrush(Qt::black);
	QPen blackPen(Qt::black);
	blackPen.setWidth(2);
	
	_northWall = new WallGraphicsItem(x, y-floor(h/4), w, 10, blackPen, blackBrush);
	_westWall = new WallGraphicsItem(x, y+floor(h*0.95), w, 10, blackPen, blackBrush);
	_southWall = new WallGraphicsItem(x, y+floor(h*0.95), w, 10, blackPen, blackBrush);
	_eastWall = new WallGraphicsItem(x+floor(w*0.95), y, 10, h, blackPen, blackBrush);

	Walls walls = cell.getWalls();

	buildWalls(walls);
}*/

CellGraphicsItem::~CellGraphicsItem()
{
	// delete managé par _scene->destroyItemGroup dans ~MainWindow()
}

/*
TODO
CellGraphicsItem& CellGraphicsItem::operator=(CellGraphicsItem &c)
{
	std::cout << "operator" << std::endl;

	if(this == &c)
	{
		return *this;
	}
	else
	{
		_rect = c._rect;
		_pen = c._pen;
		_brush = c._brush;

		*_northWall = c.getNorthWall();
		*_westWall = c.getWestWall();
		*_southWall = c.getSouthWall();
		*_eastWall = c.getEastWall();

		//_walls = new WallGraphicsItem*[4];

		//_walls = c._walls;

		int x = c._rect.x();
		int y = c._rect.y();
		int w = c._rect.width();
		int h = c._rect.height();

		QBrush blackBrush(Qt::black);
		QPen blackPen(Qt::black);
		blackPen.setWidth(2);



		_walls[0] = new WallGraphicsItem(x, y-floor(h/4), w, 10, blackPen, blackBrush);
		_walls[1] = new WallGraphicsItem(x-floor(w/4), y, 10, h, blackPen, blackBrush);
		_walls[2] = new WallGraphicsItem(x, y+floor(h*0.75), w, 10, blackPen, blackBrush);
		_walls[3] = new WallGraphicsItem(x+floor(w*0.75), y, 10, h, blackPen, blackBrush);

		for (int i = 0; i < 4; ++i)
		{
			addToGroup(_walls[i]);
		}

		return *this;
	}
}*/
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