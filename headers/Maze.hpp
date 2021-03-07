#ifndef MAZE_HPP
#define MAZE_HPP

#include "Cell.hpp"

class Maze // TODO
{
	private :

		int _width;
		int _height;

		Cell **_grid;

	public :
		Maze();
		Maze(const Maze &m); // TODO
		~Maze();

		Maze &operator=(const Maze &m); // TODO


};


#endif