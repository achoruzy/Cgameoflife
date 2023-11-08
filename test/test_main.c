// Copyright (C) Arkadiusz Choruży

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "test_suite.h"

#include "../src/logic/convay_rules.h"
#include "../src/logic/cell.h"
#include "../src/logic/cell_utils.h"

void main()
{
     TEST_START();

     TEST(ASSERT_TRUE(isToRevive(3)),
          "logic/convay_rules.c: isToRevive returns true if param ==3");
     TEST(ASSERT_FALSE(isToRevive(2)),
          "logic/convay_rules.c: isToRevive returns false if param <3");
     TEST(ASSERT_FALSE(isToRevive(4)),
          "logic/convay_rules.c: isToRevive returns false if param >3");

     TEST(ASSERT_TRUE(isToLive(2)),
          "logic/convay_rules.c: isToRevive returns true if param ==2");
     TEST(ASSERT_TRUE(isToLive(3)),
          "logic/convay_rules.c: isToRevive returns true if param ==3");
     TEST(ASSERT_FALSE(isToLive(0)),
          "logic/convay_rules.c: isToRevive returns false if param !=(0 || 3)");

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
               "logic/cell_utils.c: CellNeighborsQty returns properly calculated value 8");

          int calculated_neighbors_0 = CellNeighborsQty(10, 10, dummy_arr, dummy_len);
          TEST(ASSERT_EQ(calculated_neighbors_0, 0),
               "logic/cell_utils.c: CellNeighborsQty returns properly calculated value 0");

          int calculated_neighbors_3 = CellNeighborsQty(5, 5, dummy_arr, dummy_len);
          TEST(ASSERT_EQ(calculated_neighbors_3, 3),
               "logic/cell_utils.c: CellNeighborsQty returns properly calculated value 3");

          free(dummy_arr);
     }

     {
          int side_len = 3;
          int len = side_len * side_len;
          Cell *dummy_arr = CellArray(len);
          Cell *survived_dummy_arr = CellArray(len);

          int i = 0;
          for (int xi = 0; xi < side_len; xi++)
          {
               for (int yi = 0; yi < side_len; yi++)
               {
                    dummy_arr[i] = (Cell){xi, yi, true, 8};
                    // printf("%i, %i\n", xi, yi);
                    // printf("%i, %i, %i, %i\n", dummy_arr[i].x, dummy_arr[i].y, dummy_arr[i].isDead, dummy_arr[i].neighbours);
                    i++;
               }
          }
          int survivedCells = HandleExistingCells(&survived_dummy_arr, dummy_arr, len);

          // for (int k = 0; k < survivedCells; k++)
          // {
          // printf("%i, %i, %i, %i\n", survived_dummy_arr[k].x, survived_dummy_arr[k].y, survived_dummy_arr[k].isDead, survived_dummy_arr[k].neighbours);
          // }
          TEST(ASSERT_EQ(survivedCells, 4),
               "logic/cell_utils.c: HandleExistingCells has proper length");
          TEST(ASSERT_EQ(dummy_arr[0].x, survived_dummy_arr[0].x),
               "logic/cell_utils.c: HandleExistingCells updates array properly");
          TEST(ASSERT_EQ(dummy_arr[len - 1].y, survived_dummy_arr[survivedCells - 1].y),
               "logic/cell_utils.c: HandleExistingCells updates array properly");

          free(dummy_arr);
          free(survived_dummy_arr);
     }

     TEST_END();
}