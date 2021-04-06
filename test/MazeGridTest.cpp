#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MazeGridTests

#include <boost/test/unit_test.hpp>
#include <utility>
#include <iostream>
#include <string>

#include "MazeGrid.hpp"

using boost::unit_test::test_suite;

///////////////// BOOST Test fixture
struct MazeFixture
{
	MazeGrid grid; // is initialized with all walls built there
	std::pair<int, int> testedCell;

	MazeFixture() : grid(20, 20, std::make_pair(0, 5), std::make_pair(19, 19), true),
	testedCell(std::make_pair(2, 2))
	{
	}

	~MazeFixture()
	{
	}

	std::string checkWalls(Walls &walls)
	{
		std::string wallsState = "";

		// uppercase means "wall built"
		// lowercase means "no wall"
		wallsState += walls.hasNorthWall() ? "N" : "n";
		wallsState += walls.hasWestWall() ? "W" : "w";
		wallsState += walls.hasSouthWall() ? "S" : "s";
		wallsState += walls.hasEastWall() ? "E" : "e";

		return wallsState;
	}

	bool checkIsInNeighbors(std::pair<int, int> cell)
	{
		bool north = (cell.first == testedCell.first-1) && (cell.second == testedCell.second);
		bool west = (cell.first == testedCell.first) && (cell.second == testedCell.second-1);
		bool south = (cell.first == testedCell.first+1) && (cell.second == testedCell.second);
		bool east = (cell.first == testedCell.first) && (cell.second == testedCell.second+1);

		return (north || west || south || east);
	}
};

BOOST_FIXTURE_TEST_SUITE(s, MazeFixture)

/////////////////TESTING CARVE FUNCTION IN THE 4 DIRECTIONS (4 NEXT UNIT TESTS)
BOOST_FIXTURE_TEST_CASE(CarvingEast, MazeFixture)
{
	/// carving east

	std::pair<int, int> destCell = std::make_pair(testedCell.first, testedCell.second+1);

	grid.carve(testedCell, destCell);

	Walls firstCellWalls = grid.getCell(testedCell.first, testedCell.second).getWalls();
	Walls secondCellWalls = grid.getCell(destCell.first, destCell.second).getWalls();

	// uppercase means "wall built"
	// lowercase means "no wall"
	// ex : the next line means "all walls built except eastern one"
	BOOST_CHECK_EQUAL("NWSe", checkWalls(firstCellWalls));
	BOOST_CHECK_EQUAL("NwSE", checkWalls(secondCellWalls));
}

BOOST_FIXTURE_TEST_CASE(CarvingSouth, MazeFixture)
{
	/// carving south

	std::pair<int, int> destCell = std::make_pair(testedCell.first+1, testedCell.second);

	grid.carve(testedCell, destCell);

	Walls firstCellWalls = grid.getCell(testedCell.first, testedCell.second).getWalls();
	Walls secondCellWalls = grid.getCell(destCell.first, destCell.second).getWalls();

	// uppercase means "wall built"
	// lowercase means "no wall"
	BOOST_CHECK_EQUAL("NWsE", checkWalls(firstCellWalls));
	BOOST_CHECK_EQUAL("nWSE", checkWalls(secondCellWalls));
}

BOOST_FIXTURE_TEST_CASE(CarvingWest, MazeFixture)
{
	/// carving west

	std::pair<int, int> destCell = std::make_pair(testedCell.first, testedCell.second-1);

	grid.carve(testedCell, destCell);

	Walls firstCellWalls = grid.getCell(testedCell.first, testedCell.second).getWalls();
	Walls secondCellWalls = grid.getCell(destCell.first, destCell.second).getWalls();

	// uppercase means "wall built"
	// lowercase means "no wall"
	BOOST_CHECK_EQUAL("NwSE", checkWalls(firstCellWalls));
	BOOST_CHECK_EQUAL("NWSe", checkWalls(secondCellWalls));
}

BOOST_FIXTURE_TEST_CASE(CarvingNorth, MazeFixture)
{
	/// carving north

	std::pair<int, int> destCell = std::make_pair(testedCell.first-1, testedCell.second);

	grid.carve(testedCell, destCell);

	Walls firstCellWalls = grid.getCell(testedCell.first, testedCell.second).getWalls();
	Walls secondCellWalls = grid.getCell(destCell.first, destCell.second).getWalls();

	// uppercase means "wall built"
	// lowercase means "no wall"
	BOOST_CHECK_EQUAL("nWSE", checkWalls(firstCellWalls));
	BOOST_CHECK_EQUAL("NWsE", checkWalls(secondCellWalls));
}

/////////////////TESTING getNeighbors FUNCTION

BOOST_FIXTURE_TEST_CASE(GetNeighbors, MazeFixture)
{
	std::vector<std::pair<int, int>> neighbors = grid.getNeighbors(testedCell);

	bool inNeighbors = true;

	std::vector<std::pair<int, int>>::iterator it = neighbors.begin();
	std::vector<std::pair<int, int>>::iterator neighborEnd = neighbors.end();

	while(inNeighbors && it != neighborEnd)
	{
		inNeighbors = checkIsInNeighbors(*it);
		++it;
	}

	BOOST_CHECK_EQUAL(inNeighbors, true);
}

/////////////////TESTING chooseRandomNeighbors FUNCTION

BOOST_FIXTURE_TEST_CASE(RandomNeighbor, MazeFixture)
{
	std::pair<int, int> neighbor = grid.chooseRandomNeighbors(testedCell.first, testedCell.second);

	BOOST_CHECK_EQUAL(checkIsInNeighbors(neighbor), true);
}

/////////////////TESTING hasVisitedNeighbor FUNCTION
BOOST_FIXTURE_TEST_CASE(hasVisitedNeighbor, MazeFixture)
{
	grid.getCell(testedCell.first+1, testedCell.second).setVisited(true);

	std::pair<int, int> validNeighbor;
	BOOST_CHECK_EQUAL(grid.hasVisitedNeighbor(testedCell, validNeighbor), true);
}

/////////////////TESTING isDeadEnd FUNCTION

BOOST_FIXTURE_TEST_CASE(isDeadEnd, MazeFixture)
{
	grid.getCell(testedCell.first, testedCell.second).setVisited(true);
	grid.getCell(testedCell.first+1, testedCell.second).setVisited(true);
	grid.getCell(testedCell.first-1, testedCell.second).setVisited(true);
	grid.getCell(testedCell.first, testedCell.second+1).setVisited(true);
	grid.getCell(testedCell.first, testedCell.second-1).setVisited(true);

	BOOST_CHECK_EQUAL(grid.isDeadEnd(testedCell), true);
}

BOOST_AUTO_TEST_SUITE_END()