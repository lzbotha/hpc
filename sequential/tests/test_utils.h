#ifndef _UTILS_TEST
#define _UTILS_TEST

#include <cppunit/TestFixture.h>
#include "test_utils.h"

class TestUtils : public CppUnit::TestFixture {
    private:

    public:
        // Memory managemenet stuff
        void setUp();
        void tearDown();

        // Test cases
        void testFileReading();
        void testFileWriting();
};

#endif