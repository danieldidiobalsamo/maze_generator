#ifndef ENGINE_FACADE_HPP
#define ENGINE_FACADE_HPP

#include "Maze.hpp"

#include <string>
#include <utility>

class EngineFacade
{
	private :
		int _mazeWidth;
		int _mazeHeight;
		std::pair<int, int> _entryPos;
		std::pair<int, int> _exitPos;
		Maze _maze;

	public :

		EngineFacade();
		EngineFacade(int w, int h);
		EngineFacade(int w, int h, std::pair<int, int> entryPos, std::pair<int, int> exitPos, bool allWallsBuilt);
		~EngineFacade();

		EngineFacade& operator=(const EngineFacade &f);

		void initMaze();
		void generateMaze(std::string algo);

		// generation algo

		void huntAndKill();
		void recursiveBacktrace();
};

#endif