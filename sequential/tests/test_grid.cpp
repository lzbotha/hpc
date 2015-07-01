#include <iostream>

#include "test_grid.h"

void TestGrid::setUp() {
    using namespace std;
    g = new Grid(10, 10);
}

void TestGrid::tearDown() {
    delete g;
}

void TestGrid::testBasics() {
    using namespace std;
    CPPUNIT_ASSERT_EQUAL(10, g->rows());
    CPPUNIT_ASSERT_EQUAL(10, g->cols());

    for (int i = 0; i < 100; ++i)
        (*g)[i] = i;

    for (int i = 0; i < 100; ++i)
        CPPUNIT_ASSERT_EQUAL(i, (*g)[i]);
}