#ifndef WALL_WIDGET_HPP
#define WALL_WIDGET_HPP

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QRect>
#include <QRectF>
#include <QPaintEvent>


class WallGraphicsItem : public QGraphicsItem
{
	private :
		QRect _rect;
		QPen _pen;
		QBrush _brush;

	public : 
		WallGraphicsItem();
		WallGraphicsItem(int x, int y, int w, int h, QPen &pen, QBrush &brush);
		~WallGraphicsItem();

		// implements virtual pure function from QGraphicsItem
		QRectF boundingRect() const;
		void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif