#include "../Funciones_TPI.h"
#include "../ejercicios.h"

#include "gtest/gtest.h"
#include <iostream>
#include <string>

using namespace std;


TEST(mejorUmbralTEST, testUMBRAL) {
    int frecuencia, profundidad,duracion;
    lista_distancias dst_spk;
    vector<string> lista_archivos = {"datos/spkr0.dat",
                                     "datos/spkr1.dat",
                                     "datos/spkr2.dat",
                                     "datos/spkr4.dat",
                                     "datos/spkr5.dat"};
    sala m = cargarSalaAudio(lista_archivos,frecuencia,profundidad,duracion);
    encontrarMejorUmbralFuerzaBruta(m,frecuencia,profundidad);
}

/*
TEST(mejorUmbralTEST, testSILENCIOS) {
    int frecuencia, profundidad,duracion;
    //liprofsta_distancias dst_spk;
    vector<string> lista_archivos = {"datos/spkr0.dat",
                                     "datos/spkr1.dat",
                                     "datos/spkr2.dat",
                                     "datos/spkr4.dat",
                                     "datos/spkr5.dat"};
    sala m = cargarSalaAudio(lista_archivos,frecuencia,profundidad,duracion);
    cout << encontrarMejorIntervaloSilencios(m, frecuencia, profundidad, 27000) << endl;
}*/