#include <iostream>

#include "test_utils.h"
#include "../utils.h"

void TestUtils::setUp() {
    using namespace std;
    arr = utils::readFile("../../data/Points_[1.0e+01]_Noise_[030]_Normal.bin");
}

void TestUtils::tearDown() {
    delete [] arr;
}

void TestUtils::testFileReading() {
    using namespace std;

    // Test for getting a file size
    CPPUNIT_ASSERT_EQUAL(
        utils::getFileSize("../../data/Points_[1.0e+01]_Noise_[030]_Normal.bin"),
        10 * 8
    );

    // Test for reading in a file
    for (int i = 0; i < 10; ++i) {
        cout << arr[i*2] << "\t";
        cout << arr[i*2+1] << endl;
    }




    CPPUNIT_ASSERT_EQUAL(1, 1);
}

// void TestUtils::testFileWriting() {
//     using namespace std;
//     // Test for writing a 2D array to a file

//     utils::outputToCSV(arr, "test.csv");

//     CPPUNIT_ASSERT_EQUAL(1, 1);
// }