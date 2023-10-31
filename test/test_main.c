// Copyright (C) Arkadiusz Choruży

#include <stdio.h>
#include "test_suite.h"

#include "../src/logic/convay_rules.h"

void main()
{
    TEST_START();

    TEST(ASSERT_TRUE(isToRevive(3)),
         "convay_rules.c: isToRevive returns true if param ==3");
    TEST(ASSERT_FALSE(isToRevive(2)),
         "convay_rules.c: isToRevive returns false if param <3");
    TEST(ASSERT_FALSE(isToRevive(4)),
         "convay_rules.c: isToRevive returns false if param >3");

    TEST(ASSERT_TRUE(isToLive(2)),
         "convay_rules.c: isToRevive returns true if param ==2");
    TEST(ASSERT_TRUE(isToLive(3)),
         "convay_rules.c: isToRevive returns true if param ==3");
    TEST(ASSERT_FALSE(isToLive(0)),
         "convay_rules.c: isToRevive returns false if param !=(0 || 3)");

    TEST_END();
}