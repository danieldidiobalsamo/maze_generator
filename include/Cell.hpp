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
		int _row;
		int _col;

		bool _visited;
		bool _isEntry;
		bool _isExit;

		Walls _walls;

	public :
		Cell();
		Cell(int row, int col, bool built, bool isEntry, bool isExit);
		Cell(const Cell &c);
		~Cell();
		Cell &operator=(const Cell &c);

		bool isVisited();
		void setVisited();

		Walls getWalls() const;
		void setWalls(bool north, bool west, bool south, bool east);
};

#endif