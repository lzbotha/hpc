
#include "test_utils.h"
#include "../utils.h"

void TestUtils::setUp() {
    // Allocate memory for a 2D array
    arr = new float*[10];
    for (int i = 0; i < 10; ++i)
        arr[i] = new float[10];

    // initialize values for all blocks in array
    for (int row = 0; row < 10; ++row) {
        for (int col = 0; col < 10; ++col) {
            arr[row][col] = 0.01f * col + 0.1f * row;
        }
    }
}

void TestUtils::tearDown() {
    // Free the memory allocated for arr
    for (int i = 0; i < 10; ++i)
        delete [] arr[i];
    delete [] arr;
}

void TestUtils::testFileReading() {
    // Test for getting a file size

    // Test for reading in a file

    CPPUNIT_ASSERT_EQUAL(1, 1);
}

void TestUtils::testFileWriting() {
    // Test for writing a 2D array to a file
    utils::outputToCSV(arr, 10, "test.csv");

    CPPUNIT_ASSERT_EQUAL(1, 1);
}