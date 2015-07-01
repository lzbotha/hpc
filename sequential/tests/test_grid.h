#ifndef _GRID_TEST
#define _GRID_TEST

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "../grid.h"

class TestGrid : public CppUnit::TestFixture {

    CPPUNIT_TEST_SUITE(TestGrid);
    CPPUNIT_TEST(testBasics);
    CPPUNIT_TEST_SUITE_END();

    private:
        Grid * g;

    public:
        // Memory managemenet stuff
        void setUp();
        void tearDown();

        // Test cases
        void testBasics();
};

CPPUNIT_TEST_SUITE_REGISTRATION( TestGrid );

#endif