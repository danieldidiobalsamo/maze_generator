#ifndef CELL_HPP
#define CELL_HPP

#include "Walls.hpp"

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

		void setVisited(bool visited);
		bool isVisited() const;

		Walls getWalls() const;
		void setWalls(bool north, bool west, bool south, bool east);
		void setNorthWall(bool built);
		void setWestWall(bool built);
		void setSouthWall(bool built);
		void setEastWall(bool built);
};

#endif