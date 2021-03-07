#ifndef CELLTEST_HPP
#define CELLTEST_HPP

#include <boost/test/unit_test.hpp>

#include "Cell.hpp"

using boost::unit_test::test_suite;

BOOST_AUTO_TEST_CASE(SumValue)
{
	Cell cell;

	BOOST_CHECK_EQUAL(1,1);
}

#endif
