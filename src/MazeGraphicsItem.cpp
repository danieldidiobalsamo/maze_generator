#include "MazeGraphicsItem.hpp"
#include "Cell.hpp"

#include <cmath>
#include <QRect>
#include <QBrush>
#include <QPen>
#include <iostream>

//////////////////////////////////////////////////////////////////
// constructors
MazeGraphicsItem::MazeGraphicsItem()
{
	_mazeWidth = 0;
	_mazeHeight = 0;
	
	_cellWidth = 0;
	_cellHeight = 0;

	_grid = nullptr;
}

MazeGraphicsItem::MazeGraphicsItem(int mazeWidth, int mazeHeight, int cellWidth, int cellHeight, Maze &maze)
{
	_mazeWidth = mazeWidth;
	_mazeHeight = mazeHeight;

	_cellWidth = cellWidth;
	_cellHeight = cellHeight;

	_grid = new CellGraphicsItem*[_mazeHeight];

	QBrush yellowBrush(Qt::lightGray);
	QPen yellowPen(Qt::lightGray);
	yellowPen.setWidth(2);

	int currentX, currentY;

	for (int row = 0; row < _mazeHeight; ++row)
	{
		_grid[row] = new CellGraphicsItem[_mazeWidth];

		for (int col = 0; col < _mazeWidth; ++col)
		{
			currentX = floor(_cellWidth/2) + row * _cellWidth;
			currentY = floor(_cellHeight/2) + col * _cellHeight;

			//_grid[row][col] = CellGraphicsItem(currentX, currentY, _cellWidth, _cellHeight, yellowPen, yellowBrush, maze.getCell(row, col));
			_grid[row][col].generate(currentX, currentY, _cellWidth, _cellHeight, maze.getCell(row, col));

			addToGroup(&_grid[row][col]);
		}
	}
}

MazeGraphicsItem::~MazeGraphicsItem()
{
	if(_grid != nullptr)
	{
		for (int row = 0; row < _mazeHeight; ++row)
		{
			delete[] _grid[row];
		}

		delete[] _grid;
	}

}

//////////////////////////////////////////////////////////////////
// implements virtual pure function from QGraphicsItem

QRectF MazeGraphicsItem::boundingRect() const
{
	return QRectF(0, 0, _mazeWidth, _mazeHeight);
}

void MazeGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	Q_UNUSED(option);
	Q_UNUSED(widget);
	Q_UNUSED(painter);
}
//////////////////////////////////////////////////////////////////