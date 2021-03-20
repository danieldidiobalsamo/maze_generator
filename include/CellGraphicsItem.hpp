#ifndef CELL_WIDGET_HPP
#define CELL_WIDGET_HPP


#include <QGraphicsItemGroup>
#include <QGraphicsScene>
#include <QPainter>
#include <QRect>
#include <QRectF>
#include <QPaintEvent>
#include <vector>

#include "WallGraphicsItem.hpp"
#include "Cell.hpp"

class CellGraphicsItem : public QGraphicsItemGroup
{
	private :
		
		QRect _rect;
		QPen _pen;
		QBrush _brush;
		
		// walls that can be built
		WallGraphicsItem *_northWall;
		WallGraphicsItem *_westWall;
		WallGraphicsItem *_southWall;
		WallGraphicsItem *_eastWall;

		void buildWalls(Walls &walls);

	public :

		CellGraphicsItem();
		//CellGraphicsItem(int x, int y, int w, int h, QPen &pen, QBrush &brush, const Cell &cell);
		~CellGraphicsItem();

		//TODO
		//CellGraphicsItem& operator=(CellGraphicsItem &c);

		// implements virtual pure function from QGraphicsItem
		QRectF boundingRect() const;
		void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

		void setRect(QRect rect);

		/*WallGraphicsItem getNorthWall();
		WallGraphicsItem getWestWall();
		WallGraphicsItem getSouthWall();
		WallGraphicsItem getEastWall();*/

		void generate(int x, int y, int w, int h, const Cell &cell);

};

#endif