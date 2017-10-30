#include "../Funciones_TPI.h"
#include "../ejercicios.h"
#include "gtest/gtest.h"
#include <iostream>
#include <string>

TEST(sinSilenciosTEST, testDeSilencio1){
    //std::cout << "Sin Silencios Test" << std::endl;
    int prof = 16;
    int freq = 25;
    int umbral = 1;
    audio a = {0,0,0,0,0,0,0,0,0,6,2,3,0,0,0,0,0,10,6,0,0,3};
    audio res = {6, 2, 3, 10, 6, 0, 0, 3};
    audio  sinSilen = sinSilencios(a, silencios(a, prof, freq, umbral), freq, prof, umbral);

    std::cout << "sinSilen = {";
    for(int i = 0; i < sinSilen.size(); i++){
        std::cout << sinSilen[i] << ((i != (sinSilen.size() - 1)) ? ", " : "");
    }
    std::cout  << "}" << std::endl;

    EXPECT_EQ(sinSilen, res);
}

TEST(sinSilenciosTEST, testDeSilencio2){
    //std::cout << "Sin Silencios Test" << std::endl;
    int prof = 32;
    int freq = 45;
    int umbral = 1;
    audio a = {10,12,35,44,35,42,55,78,0,2,3,4,0,0,0,0,0,0,10,14,11};
    audio res = {10,12,35,44,35,42,55,78,0,2,3,4,0,10,14,11};
    audio  sinSilen = sinSilencios(a, silencios(a, prof, freq, umbral), freq, prof, umbral);

    std::cout << "sinSilen = {";
    for(int i = 0; i < sinSilen.size(); i++){
        std::cout << sinSilen[i] << ((i != (sinSilen.size() - 1)) ? ", " : "");
    }
    std::cout  << "}" << std::endl;

    EXPECT_EQ(sinSilen, res);
}