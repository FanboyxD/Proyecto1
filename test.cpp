#include <gtest/gtest.h>
#include "MPointer.h"

TEST(MPointerGCTest, GarbageCollection) {
    MPointer<int> p1 = MPointer<int>::New();
    *p1 = 40;

    size_t initial_count = MPointerGC::Instance().GetPointerCount();

    p1 = nullptr;

    std::this_thread::sleep_for(std::chrono::seconds(2));

    size_t final_count = MPointerGC::Instance().GetPointerCount();
    EXPECT_LT(final_count, initial_count);
}
