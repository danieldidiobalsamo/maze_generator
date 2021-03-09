#ifndef WALLS_HPP
#define WALLS_HPP

class Walls
{	
	private :

		bool _westWall;
		bool _eastWall;
		bool _northWall;
		bool _southWall;

	public : 

		Walls();
		Walls(bool built);
		~Walls();

		bool hasWestWall();
		bool hasEastWall();
		bool hasNorthWall();
		bool hasSouthWall();

		void buildWestWall();
		void buildEastWall();
		void buildNorthWall();
		void buildSouthWall();

		void removeWestWall();
		void removeEastWall();
		void removeNorthWall();
		void removeSouthWall();

		void printWalls();
};

#endif