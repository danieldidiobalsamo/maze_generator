#include "BackEnd.hpp"

#include <iostream>

BackEnd::BackEnd(QObject *parent) : QObject(parent),
 _randomIntGenerator(static_cast<unsigned int>(time(0)))
{
}

BackEnd::~BackEnd()
{
	
}

void BackEnd::setMazeWidth(int width)
{
	_mazeWidth = width;
}

void BackEnd::setMazeHeight(int height)
{
	_mazeHeight = height;
}

void BackEnd::setAlgo(QString algo)
{
	_algo = algo;
}

void BackEnd::generateMaze()
{
	std::uniform_int_distribution<int> widthDistrib(0, _mazeWidth-1);

	std::pair<int, int> randomEntry = std::make_pair(0, widthDistrib(_randomIntGenerator));

	auto exit = std::make_pair(_mazeHeight-1, _mazeWidth-1);

	_engine = new EngineFacade(_mazeWidth, _mazeHeight, randomEntry, exit, true);
	_engine->generateMaze(_algo.toStdString());
}

QVariantList BackEnd::getCell(int row, int col)
{
	QVariantList cellWallsList;

	Walls walls = _engine->getMaze().getCell(row, col).getWalls();
	// note : getMaze only returns a reference

	cellWallsList << walls.hasWestWall();
	cellWallsList << walls.hasSouthWall();
	cellWallsList << walls.hasEastWall();
	cellWallsList << walls.hasNorthWall();

	return cellWallsList;

}