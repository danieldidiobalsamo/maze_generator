#ifndef CELL_WIDGET_HPP
#define CELL_WIDGET_HPP


#include <QGraphicsItemGroup>
#include <QGraphicsScene>
#include <QPainter>
#include <QRect>
#include <QRectF>
#include <QPaintEvent>

#include "WallGraphicsItem.hpp"

class CellGraphicsItem : public QGraphicsItemGroup
{
	private :
		WallGraphicsItem **_walls;
		QRect _rect;
		QPen _pen;
		QBrush _brush;

	public :

		CellGraphicsItem();
		CellGraphicsItem(int x, int y, int w, int h, QPen &pen, QBrush &brush);
		~CellGraphicsItem();

		CellGraphicsItem& operator=(const CellGraphicsItem &c);

		// implements virtual pure function from QGraphicsItem
		QRectF boundingRect() const;
		void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

		void setRect(QRect rect);
};

#endif