#ifndef _GRID_TEST
#define _GRID_TEST

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "../grid.h"

class TestGrid : public CppUnit::TestFixture {

    CPPUNIT_TEST_SUITE(TestGrid);
    CPPUNIT_TEST(testBasics);
    CPPUNIT_TEST(testIndexing);
    CPPUNIT_TEST(testPopulatingFromFile);
    CPPUNIT_TEST(testMedianFilter);
    CPPUNIT_TEST(testFileOutput);
    CPPUNIT_TEST(testPopulatingFromArray);
    CPPUNIT_TEST_SUITE_END();

    private:
        Grid * g;
        Grid * b;

    public:
        // Memory managemenet stuff
        void setUp();
        void tearDown();

        // Test cases
        void testBasics();
        void testIndexing();
        void testPopulatingFromFile();
        void testMedianFilter();
        void testFileOutput();
        void testPopulatingFromArray();
};

CPPUNIT_TEST_SUITE_REGISTRATION( TestGrid );

#endif