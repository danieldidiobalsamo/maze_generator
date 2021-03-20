#ifndef MAZE_GRAPHICSITEM_HPP
#define MAZE_GRAPHICSITEM_HPP

#include <QGraphicsItemGroup>
#include <QGraphicsScene>
#include <QPainter>
#include <QRect>
#include <QRectF>
#include <QPaintEvent>

#include <vector>

#include "CellGraphicsItem.hpp"
#include "Maze.hpp"


class MazeGraphicsItem : public QGraphicsItemGroup
{
	private :

		int _mazeWidth;
		int _mazeHeight;

		int _cellWidth;
		int _cellHeight;

		CellGraphicsItem **_grid;

	public : 
		MazeGraphicsItem();
		MazeGraphicsItem(int mazeWidth, int mazeHeight, int cellWidth, int cellHeight, Maze &maze);
		~MazeGraphicsItem();

		// implements virtual pure function from QGraphicsItem
		QRectF boundingRect() const;
		void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif