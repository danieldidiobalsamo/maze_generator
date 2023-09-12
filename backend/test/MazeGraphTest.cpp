#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <iostream>
#include <string>
#include <utility>

#include "MazeGraph.hpp"

using boost::unit_test::test_suite;

///////////////// BOOST Test fixture

struct MazeGraphFixture {
    Cell testedCell;
    Cell entry;
    Cell exit;

    int width;
    int height;

    MazeGraph graph; // is initialized with all walls built there

    MazeGraphFixture()
        : testedCell(Cell(2, 2))
        , entry(Cell(0, 1))
        , exit(Cell(4, 3))
        , width(5)
        , height(5)
        , graph(width, height, entry, exit)
    {
    }

    ~MazeGraphFixture()
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

BOOST_FIXTURE_TEST_SUITE(s, MazeGraphFixture)

/////////////////TESTING CARVE FUNCTION IN THE 4 DIRECTIONS (4 NEXT UNIT TESTS)
BOOST_FIXTURE_TEST_CASE(CarvingRight, MazeGraphFixture)
{
    /// carving right
    auto destCell = Cell(testedCell.getRow(), testedCell.getCol() + 1);

    int testedIndex = graph.mazeCoordToIndex(testedCell);
    int destIndex = graph.mazeCoordToIndex(destCell);

    graph.carve(testedIndex, destIndex);
    std::vector<CellMetadata> cellsMetadata = graph.getCellsMetadata();

    CellWalls firstCellWalls = cellsMetadata[mazeCoordToIndex(testedCell)].walls;
    CellWalls secondCellWalls = cellsMetadata[mazeCoordToIndex(destCell)].walls;

    // uppercase means "wall built"
    // lowercase means "no wall"
    // ex : the next line means "all walls built except right one"
    BOOST_CHECK_EQUAL("TLBr", checkWalls(firstCellWalls));
    BOOST_CHECK_EQUAL("TlBR", checkWalls(secondCellWalls));
}

BOOST_FIXTURE_TEST_CASE(CarvingBottom, MazeGraphFixture)
{
    /// carving bottom

    auto destCell = Cell(testedCell.getRow() + 1, testedCell.getCol());

    int testedIndex = graph.mazeCoordToIndex(testedCell);
    int destIndex = graph.mazeCoordToIndex(destCell);

    graph.carve(testedIndex, destIndex);
    std::vector<CellMetadata> cellsMetadata = graph.getCellsMetadata();

    CellWalls firstCellWalls = cellsMetadata[mazeCoordToIndex(testedCell)].walls;
    CellWalls secondCellWalls = cellsMetadata[mazeCoordToIndex(destCell)].walls;

    // uppercase means "wall built"
    // lowercase means "no wall"
    BOOST_CHECK_EQUAL("TLbR", checkWalls(firstCellWalls));
    BOOST_CHECK_EQUAL("tLBR", checkWalls(secondCellWalls));
}

BOOST_FIXTURE_TEST_CASE(CarvingLeft, MazeGraphFixture)
{
    /// carving left

    auto destCell = Cell(testedCell.getRow(), testedCell.getCol() - 1);

    int testedIndex = graph.mazeCoordToIndex(testedCell);
    int destIndex = graph.mazeCoordToIndex(destCell);

    graph.carve(testedIndex, destIndex);
    std::vector<CellMetadata> cellsMetadata = graph.getCellsMetadata();

    CellWalls firstCellWalls = cellsMetadata[mazeCoordToIndex(testedCell)].walls;
    CellWalls secondCellWalls = cellsMetadata[mazeCoordToIndex(destCell)].walls;

    // uppercase means "wall built"
    // lowercase means "no wall"
    BOOST_CHECK_EQUAL("TlBR", checkWalls(firstCellWalls));
    BOOST_CHECK_EQUAL("TLBr", checkWalls(secondCellWalls));
}

BOOST_FIXTURE_TEST_CASE(CarvingTop, MazeGraphFixture)
{
    /// carving top

    auto destCell = Cell(testedCell.getRow() - 1, testedCell.getCol());

    int testedIndex = graph.mazeCoordToIndex(testedCell);
    int destIndex = graph.mazeCoordToIndex(destCell);

    graph.carve(testedIndex, destIndex);
    std::vector<CellMetadata> cellsMetadata = graph.getCellsMetadata();

    CellWalls firstCellWalls = cellsMetadata[mazeCoordToIndex(testedCell)].walls;
    CellWalls secondCellWalls = cellsMetadata[mazeCoordToIndex(destCell)].walls;

    // uppercase means "wall built"
    // lowercase means "no wall"
    BOOST_CHECK_EQUAL("tLBR", checkWalls(firstCellWalls));
    BOOST_CHECK_EQUAL("TLbR", checkWalls(secondCellWalls));
}

BOOST_FIXTURE_TEST_CASE(getCellsMetadata, MazeGraphFixture)
{
    auto destCell = Cell(testedCell.getRow(), testedCell.getCol() + 1);

    int testedIndex = graph.mazeCoordToIndex(testedCell);
    int destIndex = graph.mazeCoordToIndex(destCell);

    graph.carve(testedIndex, destIndex);
    auto list = graph.getCellsMetadata();

    vector<CellMetadata> goodList;
    for (int i = 0; i < width * height; ++i) {
        goodList.push_back(CellMetadata { CellWalls { true, true, true, true }, false });
    }

    goodList[mazeCoordToIndex(entry)].walls.top = false;
    goodList[mazeCoordToIndex(entry)].isPath = true;

    goodList[mazeCoordToIndex(exit)].walls.bottom = false;
    goodList[mazeCoordToIndex(exit)].isPath = true;

    goodList[mazeCoordToIndex(testedCell)] = CellMetadata { CellWalls { true, true, false, true }, false };
    goodList[mazeCoordToIndex(destCell)] = CellMetadata { CellWalls { false, true, true, true }, false };

    BOOST_CHECK_EQUAL_COLLECTIONS(list.begin(), list.end(), goodList.begin(), goodList.end());
}

BOOST_AUTO_TEST_SUITE_END()