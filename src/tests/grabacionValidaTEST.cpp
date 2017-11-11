#include "../Funciones_TPI.h"
#include "../ejercicios.h"
#include "gtest/gtest.h"
#include <iostream>
#include <string>

using namespace std;

TEST(grabacionValidaTEST, unaValida) {
    int freq = 4;
    int prof = 16;
    audio a = {1,2,3,4,5,6};

    EXPECT_EQ(true,grabacionValida(a,prof,freq));
}

TEST(grabacionValidaTEST, otraValida) {
    int freq = 12;
    int prof = 32;
    audio a = {1,2,3,4,-5,6,1,2,3,4,5,6,1,2,3,4,5,6};
    EXPECT_EQ(true,grabacionValida(a,prof,freq));
}

TEST(grabacionValidaTEST, FueraDeRango){
    int freq = 12;
    int prof = 16;

    audio a = {1,2,3,int (pow(2,17))};
    EXPECT_EQ(false, grabacionValida(a,prof,freq));
}

TEST(grabacionValidaTEST, MicrofonoNoFunciona){
    int freq = 4;
    int prof = 16;

               audio a = {0,0,0,0,0,0,0,0,0,0,1,2,3,4};
    EXPECT_EQ(false, grabacionValida(a,prof,freq));
}

TEST(grabacionValidaTEST, UnSoloSilDeMas1Seg) {
    int freq = 4;
    int prof = 16;
    audio a = {4,2,6,3,0,0,0,0,5,2,0,0,0,0,0,6};
    EXPECT_EQ(false, grabacionValida(a,prof,freq));
}

TEST(grabacionValidaTEST, VariosSilDe1Seg) {
    int freq = 4;
    int prof = 16;
    audio a = {4,2,6,3,0,0,0,0,5,0,0,0,0,2,0,0,0,0,6};
    EXPECT_EQ(true, grabacionValida(a,prof,freq));
}

TEST(grabacionValidaTEST, VarioSSilDeMas1Seg) {
    int freq = 4;
    int prof = 16;
    audio a = {4,2,6,3,0,0,0,0,5,2,0,0,0,0,0,6};
    EXPECT_EQ(false, grabacionValida(a,prof,freq));
}

TEST(grabacionValidaTEST, SilAlFinal1Seg) {
    int freq = 4;
    int prof = 16;
    audio a = {4,2,6,3,0,0,0,0,5,2,0,0,0,0};
    EXPECT_EQ(true, grabacionValida(a,prof,freq));
}


TEST(grabacionValidaTEST, SilAlFinalMas1Seg) {
    int freq = 4;
    int prof = 16;
    audio a = {4,2,6,3,0,0,0,0,5,2,0,0,0,0,0};
    EXPECT_EQ(false, grabacionValida(a,prof,freq));
}
TEST(grabacionValidaTEST, SilAlFinalDistFreqNoValido) {
    int freq = 12;
    int prof = 16;
    audio a = {4,2,6,3,0,0,0,0,5,2,0,0,0,0,0,0,0,0,0,0,0,0,7,0};
    EXPECT_EQ(true, grabacionValida(a,prof,freq));
}
TEST(grabacionValidaTEST, SilAlFinalDistFreqValido) {
    int freq = 12;
    int prof = 16;
    audio a = {4,2,6,3,0,0,0,0,5,2,0,0,0,0,0,0,0,0,0,0,0,0,0};
    EXPECT_EQ(false, grabacionValida(a,prof,freq));
}

TEST(grabacionValidaTEST, UnSoloSilDe1Seg) {
    int freq = 4;
    int prof = 16;
    audio a = {4,2,6,3,0,0,0,0,5,2,0,0,0,0,6};
    EXPECT_EQ(true, grabacionValida(a,prof,freq));
}