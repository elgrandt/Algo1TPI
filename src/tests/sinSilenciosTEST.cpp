#include "../Funciones_TPI.h"
#include "../ejercicios.h"
#include "gtest/gtest.h"
#include <iostream>
#include <string>

TEST(sinSilenciosTEST, testDeSilencio){
    //std::cout << "Sin Silencios Test" << std::endl;
    int prof = 16;
    int freq = 25;
    int umbral = 1;
    audio a = {0,0,0,0,0,0,0,0,0,6,2,3,0,0,0,0,0,10,6,0,0,3};
    audio res = {2, 3, 6, 0, 0, 3};
    audio  sinSilen = sinSilencios(a, silencios(a, prof, freq, umbral), freq, prof, umbral);

    std::cout << "sinSilen = {";
    for(int i = 0; i < sinSilen.size(); i++){
        std::cout << sinSilen[i] << ((i != (sinSilen.size() - 1)) ? ", " : "");
    }
    std::cout  << "}" << std::endl;

    EXPECT_EQ(sinSilen, res);
}