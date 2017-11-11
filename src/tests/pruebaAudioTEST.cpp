
#include "../Funciones_TPI.h"
#include "../ejercicios.h"

#include "gtest/gtest.h"
#include <iostream>
#include <string>

TEST(audiosTEST, pruebasConAudiosCorrectos) {
    string nombre = "datos/spkr0.dat";
    int frecuencia,profundidad,duracion;
    audio spk0 = leerVectorAudio(nombre,frecuencia,profundidad,duracion);
    grabarVectorAudio(spk0,"pruebaAudio.txt");
    sala m = {spk0};
    grabarVectorAudio(flashElPerezoso(m,profundidad,frecuencia)[0], "pruebaAudioFlash.txt");
    grabarVectorAudio(ardillizar(m,profundidad,frecuencia)[0], "pruebaAudioArdillizado.txt");

}

TEST(audiosTEST, audioVacio) {
    string nombre = "datos/vacio.dat";
    int frecuencia,profundidad,duracion;
    audio spk0 = leerVectorAudio(nombre,frecuencia,profundidad,duracion);
   // grabarVectorAudio(spk0,"noexiste.txt");

}

TEST(audiosTEST, audioInc) {
    string nombre;
    int frecuencia,profundidad,duracion;
    audio spk0 = leerVectorAudio(nombre,frecuencia,profundidad,duracion);

}

TEST(audiosTEST, audioInc2) {
    string nombre = "datos/spkr0.dat";
    int frecuencia,profundidad,duracion;
    audio spk0 = leerVectorAudio(nombre,frecuencia,profundidad,duracion);
    subAudio(spk0,0,spk0.size()+343);
}

TEST(audiosTEST, pruebasConAudiosIncorrectos2) {
    string nombre = "datos/spkr0.dat";
    int frecuencia,profundidad,duracion;
    /*audio spk0;
    grabarVectorAudio(spk0,"pruebaAudio.txet");*/
    //dejando eso se detiene el programa

}