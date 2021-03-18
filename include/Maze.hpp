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

	public :
		Maze();
		Maze(int width, int height);
		Maze(int width, int height, bool allWallsBuilt, std::pair<int, int> entryPos, std::pair<int, int> exitPos);
		Maze(const Maze &m);
		~Maze();

		Maze &operator=(const Maze &m);


};


#endif