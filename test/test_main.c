// Copyright (C) Arkadiusz Choruży

#include <stdio.h>
#include "test_suite.h"

void main()
{
    if (ASSERT_EQ(1, 1))
        printf("true");
}