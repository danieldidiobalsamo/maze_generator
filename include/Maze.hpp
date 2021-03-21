#ifndef MAZE_HPP
#define MAZE_HPP

#include "Cell.hpp"

#include <utility> // pair
#include <random>
#include <time.h>


enum CarvingDirection
{
	CARVING_NORTH,
	CARVING_WEST,
	CARVING_SOUTH,
	CARVING_EAST
};

class Maze
{
	private :

		int _width;
		int _height;

		std::pair<int, int> _entryPos;
		std::pair<int, int> _exitPos;

		Cell **_grid;

		std::default_random_engine _randomEngine;

		void setCellWalls(int row, int col, bool north, bool west, bool south, bool east);
		std::pair<int, int> chooseRandomNeighbors(int row, int col);
		std::vector<std::pair<int, int>> getNeighbors(std::pair<int, int> cell);
		bool isDeadEnd(std::pair<int ,int> cell);

	public :
		Maze();
		Maze(int width, int height);
		Maze(int width, int height, std::pair<int, int> entryPos, std::pair<int, int> exitPos, bool allWallsBuilt);
		Maze(const Maze &m);
		~Maze();

		Maze &operator=(const Maze &m);

		Cell getCell(int row, int col) const;

		int carve(std::pair<int, int>, std::pair<int, int>);	
		void huntAndKill();
};


#endif