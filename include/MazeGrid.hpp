#ifndef MAZE_GRID_HPP
#define MAZE_GRID_HPP

#include "Cell.hpp"

#include <map>
#include <utility> // pair
#include <random>
#include <time.h>


class MazeGrid
{
	private :

		int _width;
		int _height;

		std::pair<int, int> _entryPos;
		std::pair<int, int> _exitPos;

		std::map<std::pair<int, int>, Cell> _grid;

		std::default_random_engine _randomEngine;

	public :

		MazeGrid();
		MazeGrid(int width, int height);
		MazeGrid(int width, int height, std::pair<int, int> entryPos, std::pair<int, int> exitPos, bool allWallsBuilt);
		MazeGrid(const MazeGrid &m);
		
		~MazeGrid();

		MazeGrid& operator=(const MazeGrid &m);
		
		void carve(std::pair<int, int> src, std::pair<int, int> dest);	
		std::pair<int, int> chooseRandomNeighbors(std::pair<int, int> currentCell);
		bool isDeadEnd(std::pair<int ,int> cell);
		bool hasVisitedNeighbor(std::pair<int, int> cell, std::pair<int, int> &validNeighbor);
		std::vector<std::pair<int, int>> getNeighbors(std::pair<int, int> cell);

		void setVisited(const std::pair<int, int> cell);

		bool isEmpty() const;

		Cell getCell(int row, int col);
		Cell getCell(std::pair<int, int> cell);
};

enum CarvingDirection
{
	CARVING_NORTH,
	CARVING_WEST,
	CARVING_SOUTH,
	CARVING_EAST
};

#endif