#ifndef MAZE_HPP
#define MAZE_HPP

#include "MazeGrid.hpp"

#include <utility> // pair

class Maze
{
	private :


		int _width;
		int _height;

		std::pair<int, int> _entryPos;
		std::pair<int, int> _exitPos;

		MazeGrid _grid;

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