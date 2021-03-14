#ifndef CELL_HPP
#define CELL_HPP

#include "Walls.hpp"

// enumeration used to determine if a wall is built or not
enum WallState
{
	WALL_BUILT,
	WALL_EMPTY
};

class Cell
{
	private :
		int _x;
		int _y;

		bool _visited;
		bool _isEntry;
		bool _isExit;

		Walls _walls;

	public :
		Cell();
		Cell(int x, int y, bool built, bool isEntry, bool isExit);
		Cell(const Cell &c);
		~Cell();
		Cell &operator=(const Cell &c);

		bool isVisited();
		void setVisited();
};

#endif