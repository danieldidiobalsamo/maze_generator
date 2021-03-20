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

		void setWestWall(bool built);
		void setEastWall(bool built);
		void setNorthWall(bool built);
		void setSouthWall(bool built);

		void printWalls();
};

#endif