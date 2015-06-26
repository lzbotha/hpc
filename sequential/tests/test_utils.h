#ifndef _UTILS_TEST
#define _UTILS_TEST

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class TestUtils : public CppUnit::TestFixture {

    CPPUNIT_TEST_SUITE(TestUtils);
    CPPUNIT_TEST(testFileReading);
    CPPUNIT_TEST(testFileWriting);
    CPPUNIT_TEST_SUITE_END();

    private:
        float ** arr;

    public:
        // Memory managemenet stuff
        void setUp();
        void tearDown();

        // Test cases
        void testFileReading();
        void testFileWriting();
};

CPPUNIT_TEST_SUITE_REGISTRATION( TestUtils );

#endif