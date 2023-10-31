// Copyright (C) Arkadiusz Choruży

#include <stdio.h>
#include "test_suite.h"

#include "../src/logic/convay_rules.h"
#include "../src/logic/cell.h"

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

    {
        int dummy_len = 36;
        Cell *dummy_arr = CellArray(dummy_len);

        int i = 0;
        for (int xi = 0; xi < 6; xi++)
        {
            for (int yi = 0; yi < 6; yi++)
            {
                dummy_arr[i].x = xi;
                dummy_arr[i].y = yi;
                i++;
            }
        }
        int calculated_neighbors_8 = CellNeighborsQty(2, 2, dummy_arr, dummy_len);
        TEST(ASSERT_EQ(calculated_neighbors_8, 8),
             "cell.c: CellNeighborsQty returns properly calculated value 8");

        int calculated_neighbors_0 = CellNeighborsQty(10, 10, dummy_arr, dummy_len);
        TEST(ASSERT_EQ(calculated_neighbors_0, 0),
             "cell.c: CellNeighborsQty returns properly calculated value 0");

        int calculated_neighbors_3 = CellNeighborsQty(5, 5, dummy_arr, dummy_len);
        TEST(ASSERT_EQ(calculated_neighbors_3, 3),
             "cell.c: CellNeighborsQty returns properly calculated value 3");

        free(dummy_arr);
    }

    TEST_END();
}