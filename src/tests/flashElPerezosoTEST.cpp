#include "../Funciones_TPI.h"
#include "../ejercicios.h"

#include "gtest/gtest.h"
#include <iostream>
#include <string>

using namespace std;


TEST(flashElPerezosoTEST, lecturaAudio) {
    string nombre = "datos/spkr0.dat";
    int frecuencia, profundidad,duracion;
    audio spk0 = leerVectorAudio(nombre,frecuencia,profundidad,duracion);
    grabarVectorAudio(spk0, "pruebaAudio.txt");
    sala m = {spk0};
    grabarVectorAudio(flashElPerezoso(m,profundidad,frecuencia)[0],"pruebaAudioPerezoso.txt");
    
    EXPECT_EQ(duracion, 120);
    EXPECT_EQ(duracion, spk0.size()/frecuencia);
}

TEST(flashElPerezosoTEST, audioImPar) {
    int prof = 16;
    int freq = 4;
    sala m = {
            {1,1,9,7,3,10,0,4,4,8,8,2,5,4,3,5,6,3,6},
            {5,7,8,9,2,1,0,3,2,0,3,6,2,8,2,5,7,2,6}
    };
    sala res = {
            {1,1,1,5,9,8,7,5,3,6,10,5,0,2,4,4,4,6,8,8,8,5,2,3,5,4,4,3,3,4,5,5,6,4,3,4,6},
            {5,6,7,7,8,8,9,5,2,1,1,0,0,1,3,2,2,1,0,1,3,4,6,4,2,5,8,5,2,3,5,6,7,4,2,4,6}
    };

    sala m_out = flashElPerezoso(m,prof,freq);

    for(int i=0;i<m.size();i++){
        for(int j=0;j<res[i].size();j++) {
            //cout <<"salida : " << m_out[i][j]<<endl;
            EXPECT_EQ(res[i][j],m_out[i][j]);
        }
    }
}

TEST(flashElPerezosoTEST, audioPar) {
    int prof = 16;
    int freq = 4;
    sala m = {
            {1,1,9,7,3,10,0,4,4,8,8,2,5,4,3,5,6,3},
            {5,7,8,9,2,1,0,3,2,0,3,6,2,8,2,5,7,2}
    };
    sala res = {
            {1,1,1,5,9,8,7,5,3,6,10,5,0,2,4,4,4,6,8,8,8,5,2,3,5,4,4,3,3,4,5,5,6,4,3},
            {5,6,7,7,8,8,9,5,2,1,1,0,0,1,3,2,2,1,0,1,3,4,6,4,2,5,8,5,2,3,5,6,7,4,2}
    };

    sala m_out = flashElPerezoso(m,prof,freq);

    for(int i=0;i<m.size();i++){
        for(int j=0;j<res[i].size();j++) {
            //cout <<"salida : " << m_out[i][j]<<endl;
            EXPECT_EQ(res[i][j],m_out[i][j]);
        }
    }
}