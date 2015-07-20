#include <iostream>
#include <cmath>
#include "test_grid.h"
#include "../utils.h"

void TestGrid::setUp() {
    using namespace std;
    g = new Grid(10, 10);
    b = new Grid(512, 512);
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

void TestGrid::testPopulatingFromFile() {
    using namespace std;
    g->clear();
    g->populateFromFile("Points_[1.0e+01]_Noise_[030]_Normal.bin");

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

void TestGrid::testMedianFilter() {
    using namespace std;
    g->clear();
    b->clear();
    for (int r = 0; r < 10; ++r) {
        for (int c = 0; c < 10; ++c) {
            (*g)(r,c) = 10;
            if (r == c)
                (*g)(r,c) = 100000;
        }
    }

    g->applyMedianFilter(21);

    for (int r = 0; r < 10; ++r) {
        for (int c = 0; c < 10; ++c) {
            if (10 != (*g)(r,c)){
                cout << "r: " << r << " c: " << c << endl;
                g->print();
            }
            CPPUNIT_ASSERT_EQUAL(10, (*g)(r,c));
        }
    }
    
    for (int r = 0; r < 512; ++r) {
        for (int c = 0; c < 512; ++c) {
            (*b)(r,c) = 10;
            if (r == c)
                (*b)(r,c) = 100000;
        }
    }

    b->applyMedianFilter(21);

    for (int r = 0; r < 512; ++r) {
        for (int c = 0; c < 512; ++c) {
            if (10 != (*b)(r,c)){
                cout << "r: " << r << " c: " << c << endl;
            }
            CPPUNIT_ASSERT_EQUAL(10, (*b)(r,c));
        }
    }
}

void TestGrid::testFileOutput() {
    g->clear();
    for (int row = 0; row < 10; ++row)
        for (int col = 0; col < 10; ++col)
            (*g)(row, col) = 10 * row + col;

    g->printToFile("grid_output.csv");
}

void TestGrid::testPopulatingFromArray() {
    g->clear();

    int points = utils::getFileSize("Points_[1.0e+01]_Noise_[030]_Normal.bin") / 4 / 2;
    float * values = utils::readFile("Points_[1.0e+01]_Noise_[030]_Normal.bin");

    g->populateFromArray(points, values);

    // std::cout << std::endl;
    // g->print();

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