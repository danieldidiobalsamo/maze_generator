#ifndef MAZE_HPP
#define MAZE_HPP

#include "Cell.hpp"

#include <utility> // pair

class Maze
{
	private :

		int _width;
		int _height;

		Cell **_grid;
		void setCellWalls(int row, int col, bool north, bool west, bool south, bool east);
		

	public :
		Maze();
		Maze(int width, int height);
		Maze(int width, int height, std::pair<int, int> entryPos, std::pair<int, int> exitPos, bool allWallsBuilt);
		Maze(const Maze &m);
		~Maze();

		Maze &operator=(const Maze &m);

		Cell getCell(int row, int col) const;

		void huntAndKill();
};


#endif