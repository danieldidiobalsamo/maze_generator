#ifndef WALL_WIDGET_HPP
#define WALL_WIDGET_HPP

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QRect>
#include <QRectF>
#include <QPaintEvent>


class WallWidget : public QGraphicsItem
{
	private :
		QRect _rect;
		QPen _pen;
		QBrush _brush;

	public : 
		WallWidget();
		WallWidget(int x, int y, int w, int h, QPen &pen, QBrush &brush);
		~WallWidget();

		// implements virtual pure function from QGraphicsItem
		QRectF boundingRect() const;
		void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif