#define BOOST_TEST_DYN_LINK

#include "Maze.hpp"

#include <boost/test/unit_test.hpp>

using boost::unit_test::test_suite;

struct MazeFixture {
    Cell testedCell;
    Cell entry;
    Cell exit;

    int width;
    int height;

    Maze maze;

    MazeFixture()
        : entry(Cell(0, 0))
        , exit(Cell(39, 39))
        , width(40)
        , height(40)
        , maze(width, height, entry, exit)
    {
    }

    ~MazeFixture()
    {
    }
};

BOOST_FIXTURE_TEST_SUITE(s, MazeFixture)

BOOST_FIXTURE_TEST_CASE(HuntAndKill, MazeFixture)
{
    maze.generate("hunt");
    bool solutionExists = maze.solve("a_star");

    BOOST_CHECK_EQUAL(true, solutionExists);
}

BOOST_FIXTURE_TEST_CASE(backtracking, MazeFixture)
{
    maze.generate("backtracking");
    bool solutionExists = maze.solve("a_star");

    BOOST_CHECK_EQUAL(true, solutionExists);
}

BOOST_AUTO_TEST_SUITE_END()