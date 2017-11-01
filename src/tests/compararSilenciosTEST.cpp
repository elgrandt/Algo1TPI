#include "../Funciones_TPI.h"
#include "../ejercicios.h"
#include "gtest/gtest.h"
#include <iostream>
#include <string>

using namespace std;

TEST(compararSilenciosTEST, testArchivos) {
    vector<string> lista_archivos = {"datos/spkr0.dat",
                                     "datos/spkr1.dat",
                                     "datos/spkr2.dat",
                                     "datos/spkr4.dat"};
    int frecuencia, profundidad,duracion;
    sala m = cargarSalaAudio(lista_archivos,frecuencia,profundidad,duracion);
    float res = resultadoFinal(m, frecuencia, profundidad, UMBRAL_SILENCIO);
    EXPECT_NEAR(res,0.7931,0.001);
}