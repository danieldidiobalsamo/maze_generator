#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MazeTests

#include <boost/test/unit_test.hpp>
#include <utility>

#include "Maze.hpp"

using boost::unit_test::test_suite;

BOOST_AUTO_TEST_CASE(CarvingEast)
{
	// "normal" use of carving function

	Maze maze(20, 20, std::make_pair(0, 0), std::make_pair(19, 19), true);

	maze.carve(std::make_pair(2, 2), std::make_pair(2, 3));

	Walls w1 = maze.getCell(2, 2).getWalls();
	Walls w2 = maze.getCell(2, 3).getWalls();

	// carving removes the good wall
	BOOST_CHECK_EQUAL(w1.hasEastWall(),false);
	BOOST_CHECK_EQUAL(w2.hasWestWall(),false);

	// but don't modify other walls
	BOOST_CHECK_EQUAL(w1.hasWestWall(),true);
	BOOST_CHECK_EQUAL(w1.hasNorthWall(),true);
	BOOST_CHECK_EQUAL(w1.hasSouthWall(),true);

	BOOST_CHECK_EQUAL(w2.hasEastWall(),true);
	BOOST_CHECK_EQUAL(w2.hasNorthWall(),true);
	BOOST_CHECK_EQUAL(w2.hasSouthWall(),true);
}

BOOST_AUTO_TEST_CASE(CarvingSouth)
{
	// "normal" use of carving function

	Maze maze(20, 20, std::make_pair(0, 0), std::make_pair(19, 19), true);

	maze.carve(std::make_pair(5, 5), std::make_pair(6, 5));

	Walls w1 = maze.getCell(5, 5).getWalls();
	Walls w2 = maze.getCell(6, 5).getWalls();

	// carving removes the good wall
	BOOST_CHECK_EQUAL(w1.hasSouthWall(),false);
	BOOST_CHECK_EQUAL(w2.hasNorthWall(),false);

	// but don't modify other walls
	BOOST_CHECK_EQUAL(w1.hasWestWall(),true);
	BOOST_CHECK_EQUAL(w1.hasNorthWall(),true);
	BOOST_CHECK_EQUAL(w1.hasEastWall(),true);

	BOOST_CHECK_EQUAL(w2.hasEastWall(),true);
	BOOST_CHECK_EQUAL(w2.hasWestWall(),true);
	BOOST_CHECK_EQUAL(w2.hasSouthWall(),true);
}

BOOST_AUTO_TEST_CASE(CarvingWest)
{
	// "normal" use of carving function

	Maze maze(20, 20, std::make_pair(0, 0), std::make_pair(19, 19), true);

	maze.carve(std::make_pair(2, 3), std::make_pair(2, 2));

	Walls w1 = maze.getCell(2, 3).getWalls();
	Walls w2 = maze.getCell(2, 2).getWalls();

	// carving removes the good wall
	BOOST_CHECK_EQUAL(w1.hasWestWall(),false);
	BOOST_CHECK_EQUAL(w2.hasEastWall(),false);

	// but don't modify other walls
	BOOST_CHECK_EQUAL(w1.hasSouthWall(),true);
	BOOST_CHECK_EQUAL(w1.hasNorthWall(),true);
	BOOST_CHECK_EQUAL(w1.hasEastWall(),true);

	BOOST_CHECK_EQUAL(w2.hasNorthWall(),true);
	BOOST_CHECK_EQUAL(w2.hasWestWall(),true);
	BOOST_CHECK_EQUAL(w2.hasSouthWall(),true);
}

BOOST_AUTO_TEST_CASE(CarvingNorth)
{
	// "normal" use of carving function

	Maze maze(20, 20, std::make_pair(0, 0), std::make_pair(19, 19), true);

	maze.carve(std::make_pair(3, 2), std::make_pair(2, 2));

	Walls w1 = maze.getCell(3, 2).getWalls();
	Walls w2 = maze.getCell(2, 2).getWalls();

	// carving removes the good wall
	BOOST_CHECK_EQUAL(w1.hasNorthWall(),false);
	BOOST_CHECK_EQUAL(w2.hasSouthWall(),false);

	// but don't modify other walls
	BOOST_CHECK_EQUAL(w1.hasSouthWall(),true);
	BOOST_CHECK_EQUAL(w1.hasWestWall(),true);
	BOOST_CHECK_EQUAL(w1.hasEastWall(),true);

	BOOST_CHECK_EQUAL(w2.hasNorthWall(),true);
	BOOST_CHECK_EQUAL(w2.hasWestWall(),true);
	BOOST_CHECK_EQUAL(w2.hasEastWall(),true);
}