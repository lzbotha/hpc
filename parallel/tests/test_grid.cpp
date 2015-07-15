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

void TestGrid::testMedianFilter() {
    /**
        Tests a median filter in the top left where most of the elements are
        set to be 1.
    */
    g->clear();
    // Top row
    (*g)(0,0) = 1;
    (*g)(0,1) = 0;
    (*g)(0,2) = 0;

    // Middle row
    (*g)(1,0) = 1;
    (*g)(1,1) = 1;
    (*g)(1,2) = 1;

    // Bottom row
    (*g)(2,0) = 0;
    (*g)(2,1) = 0;
    (*g)(2,2) = 1;

    CPPUNIT_ASSERT_EQUAL(1, g->medianFilter(1, 1, 3));


    /**
        Tests a median filter in the top left where the elements are in [0, 8]
    */
    // Top row
    (*g)(0,0) = 0;
    (*g)(0,1) = 3;
    (*g)(0,2) = 6;

    // Middle row
    (*g)(1,0) = 1;
    (*g)(1,1) = 4;
    (*g)(1,2) = 7;

    // Bottom row
    (*g)(2,0) = 2;
    (*g)(2,1) = 5;
    (*g)(2,2) = 8;

    CPPUNIT_ASSERT_EQUAL(4, g->medianFilter(1, 1, 3));

    /**
        Tests a median filter in the top left corner where some elements are cur off
    */
    g->clear();
    
    // Top row
    (*g)(0,0) = 0;
    (*g)(0,1) = 1;

    // Middle row
    (*g)(1,0) = 1;
    (*g)(1,1) = 1;

    CPPUNIT_ASSERT_EQUAL(1, g->medianFilter(0, 0, 3));

    // Top row
    (*g)(0,0) = 1;
    (*g)(0,1) = 2;

    // Middle row
    (*g)(1,0) = 3;
    (*g)(1,1) = 4;    

    CPPUNIT_ASSERT_EQUAL(2, g->medianFilter(0, 0, 3));

    /**
        Tests a median filter in the top right corner where some elements are cur off
    */
    g->clear();
    
    // Top row
    (*g)(0,8) = 0;
    (*g)(0,9) = 3;

    // Middle row
    (*g)(1,8) = 3;
    (*g)(1,9) = 3;

    CPPUNIT_ASSERT_EQUAL(3, g->medianFilter(0, 9, 3));

    // Top row
    (*g)(0,8) = 5;
    (*g)(0,9) = 6;

    // Middle row
    (*g)(1,8) = 7;
    (*g)(1,9) = 8;    

    CPPUNIT_ASSERT_EQUAL(6, g->medianFilter(0, 9, 3));


    /**
        Tests a median filter in the bottom right corner where some elements are cur off
    */
    g->clear();
    
    // Top row
    (*g)(8,8) = 0;
    (*g)(8,9) = 4;

    // Middle row
    (*g)(9,8) = 4;
    (*g)(9,9) = 4;

    CPPUNIT_ASSERT_EQUAL(4, g->medianFilter(9, 9, 3));

    // Top row
    (*g)(8,8) = 5;
    (*g)(8,9) = 6;

    // Middle row
    (*g)(9,8) = 7;
    (*g)(9,9) = 8;    

    CPPUNIT_ASSERT_EQUAL(6, g->medianFilter(9, 9, 3));

    /**
        Tests a median filter in the bottom left corner where some elements are cur off
    */
    g->clear();
    
    // Top row
    (*g)(8,0) = 0;
    (*g)(8,1) = 4;

    // Middle row
    (*g)(9,0) = 4;
    (*g)(9,1) = 4;

    CPPUNIT_ASSERT_EQUAL(4, g->medianFilter(9, 0, 3));

    // Top row
    (*g)(8,0) = 5;
    (*g)(8,1) = 6;

    // Middle row
    (*g)(9,0) = 7;
    (*g)(9,1) = 8;    

    CPPUNIT_ASSERT_EQUAL(6, g->medianFilter(9, 0, 3));


    /**
        Test applying the median filter to an entire grid that needs no filter
    */
    g->clear();
    for (int i = 0; i < 100; ++i)
        (*g)[i] = 1;

    g->applyMedianFilter(3);

    for (int i = 0; i < 100; ++i)
        CPPUNIT_ASSERT_EQUAL(1, (*g)[i]);

    /**
        Test applying the median filter to an entire grid
    */
    for (int row = 0; row < 10; ++row)
        for (int col = 0; col < 10; ++col)
            if (row % 2 == 0 and col % 2 == 0)
                (*g)(row, col) = 5;
            else
                (*g)(row, col) = 1;

    g->applyMedianFilter(3);

    for (int i = 0; i < 100; ++i)
        CPPUNIT_ASSERT_EQUAL(1, (*g)[i]);


    int arr[] = {9,8,7,6,5,4,3,2,1,0};
    g->select_kth(arr, 0, 9, 9);
    g->select_kth(arr, 0, 9, 8);
    g->select_kth(arr, 0, 9, 7);
    g->select_kth(arr, 0, 9, 6);
    g->select_kth(arr, 0, 9, 5);
    g->select_kth(arr, 0, 9, 4);
    g->select_kth(arr, 0, 9, 3);
    g->select_kth(arr, 0, 9, 2);
    g->select_kth(arr, 0, 9, 1);
    g->select_kth(arr, 0, 9, 0);

    for (int i = 0; i < 10; ++i)
        CPPUNIT_ASSERT_EQUAL(i, arr[i]);
}

void TestGrid::testFileOutput() {
    g->clear();
    for (int row = 0; row < 10; ++row)
        for (int col = 0; col < 10; ++col)
            (*g)(row, col) = 10 * row + col;

    g->printToFile("grid_output.csv");
}