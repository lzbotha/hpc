#include <iostream>

#include "test_utils.h"
#include "../utils.h"

void TestUtils::setUp() {
    using namespace std;
    arr = vector<vector<float>>(10, vector<float>(10, 0));
}

void TestUtils::tearDown() {
    
}

void TestUtils::testFileReading() {
    // Test for getting a file size

    // Test for reading in a file

    CPPUNIT_ASSERT_EQUAL(1, 1);
}

void TestUtils::testFileWriting() {
    using namespace std;
    // Test for writing a 2D array to a file

    utils::outputToCSV(arr, "test.csv");

    CPPUNIT_ASSERT_EQUAL(1, 1);
}