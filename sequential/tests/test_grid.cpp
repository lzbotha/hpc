#include <iostream>
#include <cmath>
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

    g->clear();
    for(int i = 0; i < 100; ++i)
        CPPUNIT_ASSERT_EQUAL(0, (*g)[i]);
}

void TestGrid::testIndexing() {
    g->clear();

    for (int i = 0; i < 100; ++i)
        (*g)[i] = i;

    for (int i = 0; i < 100; ++i)
        CPPUNIT_ASSERT_EQUAL(i, (*g)[i]);

    for (int i = 0; i < 10; ++i)
        (*g)(i, i) = i;

    for (int i = 0; i < 10; ++i)
        CPPUNIT_ASSERT_EQUAL(i, (*g)(i, i));

    for (int i = 0; i < 100; ++i)
        (*g)[i] = i;

    CPPUNIT_ASSERT_EQUAL(0, (*g)(0, 0));
    CPPUNIT_ASSERT_EQUAL(11, (*g)(1, 1));
    CPPUNIT_ASSERT_EQUAL(22, (*g)(2, 2));
    CPPUNIT_ASSERT_EQUAL(33, (*g)(3, 3));
}

void TestGrid::testRowFetching() {
    g->clear();

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

void TestGrid::testPopulatingFromFile() {
    using namespace std;
    g->clear();
    g->populateFromFile("Points_[1.0e+01]_Noise_[030]_Normal.bin");

    // cout << endl;
    // for (int row = 0; row < 10; ++row){
    //     for (int col = 0; col < 10; ++col) {
    //         cout << (*g)(row, col) << "\t";
    //     }
    //     cout << endl;
    // }

    CPPUNIT_ASSERT_EQUAL(1, (*g)(3, 7));
    CPPUNIT_ASSERT_EQUAL(1, (*g)(3, 3));
    CPPUNIT_ASSERT_EQUAL(1, (*g)(4, 2));
    CPPUNIT_ASSERT_EQUAL(1, (*g)(4, 4));
    CPPUNIT_ASSERT_EQUAL(1, (*g)(5, 6));
    CPPUNIT_ASSERT_EQUAL(1, (*g)(5, 3));
    CPPUNIT_ASSERT_EQUAL(1, (*g)(5, 5));
    CPPUNIT_ASSERT_EQUAL(1, (*g)(6, 2));
    CPPUNIT_ASSERT_EQUAL(1, (*g)(7, 6));
    CPPUNIT_ASSERT_EQUAL(1, (*g)(9, 5));
}