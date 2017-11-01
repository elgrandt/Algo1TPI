#include "../Funciones_TPI.h"
#include "../ejercicios.h"

#include "gtest/gtest.h"
#include <iostream>
#include <string>

TEST(hayQuilomboTEST, hayQuilombo) {
    int prof = 16;
    int freq = 4;
    sala m = {
            {1,1,9,7,3,10,0,4,4,8,8,2,5,4,3,5,6,3,6},
            {5,7,8,9,2,1,0,3,2,0,3,6,2,8,2,5,7,2,6}
    };
    EXPECT_EQ(true,hayQuilombo(m,prof,freq,1));
}

TEST(hayQuilomboTEST, nohayQuilombo) {
    int prof = 16;
    int freq = 4;
    sala m = {
            {0,0,0,7,3,0,0,0,4,8,8,0,0,0,3,0,0,3,6},
            {5,7,0,0,0,1,0,3,0,0,0,6,2,0,0,5,0,0,0}
    };
    EXPECT_EQ(false,hayQuilombo(m,prof,freq,1));
}
