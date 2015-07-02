#include <iostream>

#include "test_grid.h"

void TestGrid::setUp() {
    using namespace std;
    g = new Grid(10, 10);
}

void TestGrid::tearDown() {
    // delete g;
}

void TestGrid::testBasics() {
    using namespace std;
    CPPUNIT_ASSERT_EQUAL(10, g->rows());
    CPPUNIT_ASSERT_EQUAL(10, g->cols());
}

void TestGrid::testIndexing() {
    for (int i = 0; i < 100; ++i)
        (*g)[i] = i;

    for (int i = 0; i < 100; ++i)
        CPPUNIT_ASSERT_EQUAL(i, (*g)[i]);

    for (int i = 0; i < 10; ++i)
        (*g)(i, i) = i;

    for (int i = 0; i < 10; ++i)
        CPPUNIT_ASSERT_EQUAL(i, (*g)(i, i));
}

void TestGrid::testRowFetching() {
    int start = -1;
    int end = -1;
    g->getRows(5, 3, start, end);
    CPPUNIT_ASSERT_EQUAL(2, start);
    CPPUNIT_ASSERT_EQUAL(8, end);

    g->getRows(0, 3, start, end);
    CPPUNIT_ASSERT_EQUAL(0, start);
    CPPUNIT_ASSERT_EQUAL(3, end);    

    g->getRows(9, 3, start, end);
    CPPUNIT_ASSERT_EQUAL(6, start);
    CPPUNIT_ASSERT_EQUAL(9, end);

    g->getRows(12, 3, start, end);
    CPPUNIT_ASSERT_EQUAL(-1, start);
    CPPUNIT_ASSERT_EQUAL(-1, end);

    g->getRows(5, 20, start, end);
    CPPUNIT_ASSERT_EQUAL(0, start);
    CPPUNIT_ASSERT_EQUAL(9, end);
}