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
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.475607f, arr[0], 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.282636f, arr[1], 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.636858f, arr[2], 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.284962f, arr[3], 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.506654f, arr[4], 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.648967f, arr[5], 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.506721f, arr[6], 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.394673f, arr[7], 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.592506f, arr[8], 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.540140f, arr[9], 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.924935f, arr[10], 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.574344f, arr[11], 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.704193f, arr[12], 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.656682f, arr[13], 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.474432f, arr[14], 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.432637f, arr[15], 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.362569f, arr[16], 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.761684f, arr[17], 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.345452f, arr[18], 0.00001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.395687f, arr[19], 0.00001);




    CPPUNIT_ASSERT_EQUAL(1, 1);
}

// void TestUtils::testFileWriting() {
//     using namespace std;
//     // Test for writing a 2D array to a file

//     utils::outputToCSV(arr, "test.csv");

//     CPPUNIT_ASSERT_EQUAL(1, 1);
// }