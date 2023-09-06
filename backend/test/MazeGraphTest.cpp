#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MazeGraphTests

#include <boost/test/unit_test.hpp>
#include <iostream>
#include <string>
#include <utility>

#include "MazeGraph.hpp"

using boost::unit_test::test_suite;

///////////////// BOOST Test fixture

struct MazeFixture {
    Cell testedCell;
    Cell entry;
    Cell exit;

    int width;
    int height;

    MazeGraph graph; // is initialized with all walls built there

    MazeFixture()
        : testedCell(Cell(2, 2))
        , entry(Cell(0, 0))
        , exit(Cell(4, 4))
        , width(5)
        , height(5)
        , graph(width, height, entry, exit)
    {
    }

    ~MazeFixture()
    {
    }

    std::string checkWalls(CellWalls& walls)
    {
        std::string wallsState = "";

        // uppercase means "wall built"
        // lowercase means "no wall"
        wallsState += walls.top ? "T" : "t";
        wallsState += walls.left ? "L" : "l";
        wallsState += walls.bottom ? "B" : "b";
        wallsState += walls.right ? "R" : "r";

        return wallsState;
    }

    bool checkIsInNeighbors(Cell cell)
    {
        bool top = (cell.getRow() == testedCell.getRow() - 1) && (cell.getCol() == testedCell.getCol());
        bool left = (cell.getRow() == testedCell.getRow()) && (cell.getCol() == testedCell.getCol() - 1);
        bool bottom = (cell.getRow() == testedCell.getRow() + 1) && (cell.getCol() == testedCell.getCol());
        bool right = (cell.getRow() == testedCell.getRow()) && (cell.getCol() == testedCell.getCol() + 1);

        return (top || left || bottom || right);
    }

    int mazeCoordToIndex(Cell coord)
    {
        return (width * coord.getRow()) + coord.getCol();
    }
};

BOOST_FIXTURE_TEST_SUITE(s, MazeFixture)

/////////////////TESTING CARVE FUNCTION IN THE 4 DIRECTIONS (4 NEXT UNIT TESTS)
BOOST_FIXTURE_TEST_CASE(CarvingRight, MazeFixture)
{
    /// carving right

    auto destCell = Cell(testedCell.getRow(), testedCell.getCol() + 1);

    graph.carve(testedCell, destCell);
    std::vector<CellMetadata> cellsMetadata = graph.getCellsMetadata();

    CellWalls firstCellWalls = cellsMetadata[mazeCoordToIndex(testedCell)].walls;
    CellWalls secondCellWalls = cellsMetadata[mazeCoordToIndex(destCell)].walls;

    // uppercase means "wall built"
    // lowercase means "no wall"
    // ex : the next line means "all walls built except right one"
    BOOST_CHECK_EQUAL("TLBr", checkWalls(firstCellWalls));
    BOOST_CHECK_EQUAL("TlBR", checkWalls(secondCellWalls));
}

BOOST_FIXTURE_TEST_CASE(CarvingBottom, MazeFixture)
{
    /// carving bottom

    auto destCell = Cell(testedCell.getRow() + 1, testedCell.getCol());

    graph.carve(testedCell, destCell);
    std::vector<CellMetadata> cellsMetadata = graph.getCellsMetadata();

    CellWalls firstCellWalls = cellsMetadata[mazeCoordToIndex(testedCell)].walls;
    CellWalls secondCellWalls = cellsMetadata[mazeCoordToIndex(destCell)].walls;

    // uppercase means "wall built"
    // lowercase means "no wall"
    BOOST_CHECK_EQUAL("TLbR", checkWalls(firstCellWalls));
    BOOST_CHECK_EQUAL("tLBR", checkWalls(secondCellWalls));
}

BOOST_FIXTURE_TEST_CASE(CarvingLeft, MazeFixture)
{
    /// carving left

    auto destCell = Cell(testedCell.getRow(), testedCell.getCol() - 1);

    graph.carve(testedCell, destCell);
    std::vector<CellMetadata> cellsMetadata = graph.getCellsMetadata();

    CellWalls firstCellWalls = cellsMetadata[mazeCoordToIndex(testedCell)].walls;
    CellWalls secondCellWalls = cellsMetadata[mazeCoordToIndex(destCell)].walls;

    // uppercase means "wall built"
    // lowercase means "no wall"
    BOOST_CHECK_EQUAL("TlBR", checkWalls(firstCellWalls));
    BOOST_CHECK_EQUAL("TLBr", checkWalls(secondCellWalls));
}

BOOST_FIXTURE_TEST_CASE(CarvingTop, MazeFixture)
{
    /// carving top

    auto destCell = Cell(testedCell.getRow() - 1, testedCell.getCol());

    graph.carve(testedCell, destCell);
    std::vector<CellMetadata> cellsMetadata = graph.getCellsMetadata();

    CellWalls firstCellWalls = cellsMetadata[mazeCoordToIndex(testedCell)].walls;
    CellWalls secondCellWalls = cellsMetadata[mazeCoordToIndex(destCell)].walls;

    // uppercase means "wall built"
    // lowercase means "no wall"
    BOOST_CHECK_EQUAL("tLBR", checkWalls(firstCellWalls));
    BOOST_CHECK_EQUAL("TLbR", checkWalls(secondCellWalls));
}

/////////////////TESTING getNeighbors FUNCTION

BOOST_FIXTURE_TEST_CASE(getSurroundingCells, MazeFixture)
{
    auto neighbors = graph.getSurroundingCells(testedCell);

    bool inNeighbors = true;

    auto it = neighbors.begin();
    auto neighborEnd = neighbors.end();

    while (inNeighbors && it != neighborEnd) {
        inNeighbors = checkIsInNeighbors(*it);
        ++it;
    }

    BOOST_CHECK_EQUAL(inNeighbors, true);
    BOOST_CHECK_EQUAL(neighbors.size(), 4);
}

BOOST_FIXTURE_TEST_CASE(getCellsMetadata, MazeFixture)
{
    auto destCell = Cell(testedCell.getRow(), testedCell.getCol() + 1);

    graph.carve(testedCell, destCell);
    auto list = graph.getCellsMetadata();

    vector<CellMetadata> goodList;
    for (int i = 0; i < width * height; ++i) {
        goodList.push_back(CellMetadata { CellWalls { true, true, true, true }, false });
    }

    goodList[mazeCoordToIndex(entry)] = CellMetadata { CellWalls { false, false, false, false }, true }; // entry
    goodList[mazeCoordToIndex(entry.getTopNeighbor())].walls.bottom = false;
    goodList[mazeCoordToIndex(entry.getBottomNeighbor(height))].walls.top = false;
    goodList[mazeCoordToIndex(entry.getLeftNeighbor())].walls.right = false;
    goodList[mazeCoordToIndex(entry.getRightNeighbor(width))].walls.left = false;

    goodList[mazeCoordToIndex(exit)] = CellMetadata { CellWalls { false, false, false, false }, true }; // exit
    goodList[mazeCoordToIndex(exit.getTopNeighbor())].walls.bottom = false;
    goodList[mazeCoordToIndex(exit.getBottomNeighbor(height))].walls.top = false;
    goodList[mazeCoordToIndex(exit.getLeftNeighbor())].walls.right = false;
    goodList[mazeCoordToIndex(exit.getRightNeighbor(width))].walls.left = false;

    goodList[mazeCoordToIndex(testedCell)] = CellMetadata { CellWalls { true, true, false, true }, false };
    goodList[mazeCoordToIndex(destCell)] = CellMetadata { CellWalls { false, true, true, true }, false };

    BOOST_CHECK_EQUAL_COLLECTIONS(list.begin(), list.end(), goodList.begin(), goodList.end());
}

BOOST_AUTO_TEST_SUITE_END()