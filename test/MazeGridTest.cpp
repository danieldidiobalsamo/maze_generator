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

	auto destCell = std::make_pair(testedCell.first, testedCell.second+1);

	grid.carve(testedCell, destCell);

	Walls firstCellWalls = grid.getCell(testedCell).getWalls();
	Walls secondCellWalls = grid.getCell(destCell).getWalls();

	// uppercase means "wall built"
	// lowercase means "no wall"
	// ex : the next line means "all walls built except eastern one"
	BOOST_CHECK_EQUAL("NWSe", checkWalls(firstCellWalls));
	BOOST_CHECK_EQUAL("NwSE", checkWalls(secondCellWalls));
}

BOOST_FIXTURE_TEST_CASE(CarvingSouth, MazeFixture)
{
	/// carving south

	auto destCell = std::make_pair(testedCell.first+1, testedCell.second);

	grid.carve(testedCell, destCell);

	Walls firstCellWalls = grid.getCell(testedCell).getWalls();
	Walls secondCellWalls = grid.getCell(destCell).getWalls();

	// uppercase means "wall built"
	// lowercase means "no wall"
	BOOST_CHECK_EQUAL("NWsE", checkWalls(firstCellWalls));
	BOOST_CHECK_EQUAL("nWSE", checkWalls(secondCellWalls));
}

BOOST_FIXTURE_TEST_CASE(CarvingWest, MazeFixture)
{
	/// carving west

	auto destCell = std::make_pair(testedCell.first, testedCell.second-1);

	grid.carve(testedCell, destCell);

	Walls firstCellWalls = grid.getCell(testedCell).getWalls();
	Walls secondCellWalls = grid.getCell(destCell).getWalls();

	// uppercase means "wall built"
	// lowercase means "no wall"
	BOOST_CHECK_EQUAL("NwSE", checkWalls(firstCellWalls));
	BOOST_CHECK_EQUAL("NWSe", checkWalls(secondCellWalls));
}

BOOST_FIXTURE_TEST_CASE(CarvingNorth, MazeFixture)
{
	/// carving north

	auto destCell = std::make_pair(testedCell.first-1, testedCell.second);

	grid.carve(testedCell, destCell);

	Walls firstCellWalls = grid.getCell(testedCell).getWalls();
	Walls secondCellWalls = grid.getCell(destCell).getWalls();

	// uppercase means "wall built"
	// lowercase means "no wall"
	BOOST_CHECK_EQUAL("nWSE", checkWalls(firstCellWalls));
	BOOST_CHECK_EQUAL("NWsE", checkWalls(secondCellWalls));
}

/////////////////TESTING getNeighbors FUNCTION

BOOST_FIXTURE_TEST_CASE(GetNeighbors, MazeFixture)
{
	auto neighbors = grid.getNeighbors(testedCell);

	bool inNeighbors = true;

	auto it = neighbors.begin();
	auto neighborEnd = neighbors.end();

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
	auto neighbor = grid.chooseRandomNeighbors(testedCell);

	BOOST_CHECK_EQUAL(checkIsInNeighbors(neighbor), true);
}

/////////////////TESTING hasVisitedNeighbor FUNCTION
BOOST_FIXTURE_TEST_CASE(hasVisitedNeighbor, MazeFixture)
{
	auto current = std::make_pair(testedCell.first+1, testedCell.second);

	grid.setVisited(current);

	auto [visitedNeighbor, chosenNeighbor] = grid.hasVisitedNeighbor(testedCell);
	std::ignore = chosenNeighbor;

	BOOST_CHECK_EQUAL(visitedNeighbor, true);

}

/////////////////TESTING isDeadEnd FUNCTION

BOOST_FIXTURE_TEST_CASE(isDeadEnd, MazeFixture)
{
	grid.setVisited(testedCell);
	grid.setVisited(std::make_pair(testedCell.first+1, testedCell.second));
	grid.setVisited(std::make_pair(testedCell.first-1, testedCell.second));
	grid.setVisited(std::make_pair(testedCell.first, testedCell.second+1));
	grid.setVisited(std::make_pair(testedCell.first, testedCell.second-1));

	BOOST_CHECK_EQUAL(grid.isDeadEnd(testedCell), true);
}

BOOST_AUTO_TEST_SUITE_END()