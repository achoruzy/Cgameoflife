// Copyright (C) Arkadiusz Choruży

#include <stdbool.h>
#include <stdio.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"

// TESTING ASSERTIONS
// true - false macros
#define ASSERT_EQ(a, b) (a == b)
#define ASSERT_NOT_EQ(a, b) (a != b)

bool TEST(bool ASSERTION, char *title)
{
    if (ASSERTION)
    {
        printf(ANSI_COLOR_GREEN "Test passed: %s\n", title);
        return true;
    }
    printf(ANSI_COLOR_RED "Test failed: %s\n", title);
    return false;
}