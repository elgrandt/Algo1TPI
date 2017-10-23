#include "../Funciones_TPI.h"
#include "../ejercicios.h"
#include "gtest/gtest.h"
#include <iostream>
#include <string>

using namespace std;

TEST(ardillizarTEST, audioPar) {
    int prof = 16;
    int freq = 4;
    sala m = {
            {1,2,3,4,5,6},
            {5,7,8,9,2,1}
    };
    sala res = {
            {1,3,5},
            {5,8,2}
    };

    sala m_out = ardillizar(m,prof,freq);

    for(int i=0;i<m.size();i++){
        for(int j=0;j<res[i].size();j++) {
            EXPECT_EQ(res[i][j],m_out[i][j]);
        }
    }
}

TEST(ardillizarTEST, audioImPar) {
    int prof = 16;
    int freq = 4;
    sala m = {
            {1,2,3,4,5,6,9},
            {5,7,8,9,2,1,4}
    };
    sala res = {
            {1,3,5,9},
            {5,8,2,4}
    };

    sala m_out = ardillizar(m,prof,freq);

    for(int i=0;i<m.size();i++){
        for(int j=0;j<res[i].size();j++) {
            EXPECT_EQ(res[i][j],m_out[i][j]);
        }
    }
}

