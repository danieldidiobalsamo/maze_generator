#ifndef MAZE_GRID_HPP
#define MAZE_GRID_HPP

#include "Cell.hpp"

#include <tuple>
#include <map>
#include <utility> // pair
#include <random>
#include <time.h>

typedef std::pair<int, int> CellCoord;

enum CarvingDirection
{
	CARVING_NORTH,
	CARVING_WEST,
	CARVING_SOUTH,
	CARVING_EAST
};

class MazeGrid
{
	private :

		int _width;
		int _height;

		CellCoord _entryPos;
		CellCoord _exitPos;

		std::map<CellCoord, Cell> _grid;

		std::default_random_engine _randomEngine;

	public :

		MazeGrid();
		MazeGrid(const int width, const  int height);
		MazeGrid(const int width, const int height, const CellCoord entryPos, const CellCoord exitPos, const bool allWallsBuilt);
		MazeGrid(const MazeGrid &m);
		
		~MazeGrid();

		MazeGrid& operator=(const MazeGrid &m);
		
		void carve(const CellCoord src, const CellCoord dest);	
		CellCoord chooseRandomNeighbors(const CellCoord currentCell);
		bool isDeadEnd(const CellCoord cell);
		std::tuple<bool,CellCoord> hasVisitedNeighbor(const CellCoord cell);
		std::vector<CellCoord> getNeighbors(const CellCoord cell);

		void setVisited(const CellCoord cell);

		bool isEmpty() const;

		Cell getCell(const int row, const int col);
		Cell getCell(const CellCoord cell);
};

#endif