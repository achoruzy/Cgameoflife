// Copyright (C) Arkadiusz Choruży

#include <stdbool.h>
#include <stdio.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

// TESTING ASSERTIONS
// true - false macros
#define ASSERT_EQ(a, b) (a == b)
#define ASSERT_NOT_EQ(a, b) (a != b)
#define ASSERT_TRUE(a) (a)
#define ASSERT_FALSE(a) (!a)

void TEST_START()
{
    printf("\n");
    printf(ANSI_COLOR_CYAN "TESTING STARTED" ANSI_COLOR_RESET "\n");
    printf("---------------\n");
}

void TEST_END()
{
    printf("---------------\n");
    printf("\n");
}

bool TEST(bool ASSERTION, char *title)
{
    if (ASSERTION)
    {
        printf(ANSI_COLOR_GREEN "Test passed:" ANSI_COLOR_RESET " %s\n", title);
        return true;
    }
    printf(ANSI_COLOR_RED "Test failed: " ANSI_COLOR_RESET " %s\n", title);
    return false;
}