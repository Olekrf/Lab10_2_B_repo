#include <gtest/gtest.h>

#define main app_main
#include "main.cpp"
#undef main

TEST(Lab10_2_3, BinSearchTest) {
    const int N = 3;
    Student* p = new Student[N];

    p[0] = { "Ivanenko", 1, CS, 3, 3, { 3 } };
    p[1] = { "Petrenko", 2, INFORMATICS, 4, 4, { 4 } };
    p[2] = { "Sydorenko", 3, LABOR, 5, 5, { 5 } };

    EXPECT_EQ(BinSearch(p, N, "Petrenko", 4, 4.0), 1);
    EXPECT_EQ(BinSearch(p, N, "Kovalenko", 4, 4.0), -1);

    delete[] p;
}