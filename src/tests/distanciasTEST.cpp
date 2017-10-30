
#include "../Funciones_TPI.h"
#include "../ejercicios.h"

#include "gtest/gtest.h"
#include <iostream>
#include <string>

using namespace std;
/*
TEST(distanciasTEST, subaudioLongitud) {
    audio v = {1,2,3,4,5,6};
    audio v2 = subAudio(v,2,2);
    EXPECT_EQ(2,v2.size());
}

TEST(distanciasTEST, subaudioContenido) {
    audio v = {1,2,3,4,5,6};
    audio sv = {3,4};
    audio v2 = subAudio(v,2,2);
    for(int k=0;k<sv.size();k++)
        EXPECT_EQ(sv[k],v2[k]);
}
TEST(distanciasTEST, estadisticos) {
    audio v = {6,2,3,1};
    float media, std;
    calcularEstadisticos(v,media,std);
    EXPECT_EQ(media, 3);
    EXPECT_NEAR(std, 1.87,0.1);
}

TEST(distanciasTEST, estadisticos2) {
    audio v = {0, 0, -3};
    float media, std;
    calcularEstadisticos(v, media, std);
    EXPECT_EQ(media, -1);
    EXPECT_NEAR(std, 1.4142, 0.1);
}


TEST(distanciasTEST, lecturaAudio) {
    string nombre = "datos/spkr0.dat";
    int frecuencia, profundidad,duracion;
    audio spk0 = leerVectorAudio(nombre,frecuencia,profundidad,duracion);
    EXPECT_EQ(duracion, 120);
    EXPECT_EQ(duracion, spk0.size()/frecuencia);
}
*/

TEST(distanciasTEST, testBEEP) {
    int frecuencia, profundidad,duracion;
    int startPOINT, endPOINT;
    lista_distancias dst_spk;
    vector<string> lista_archivos = {"datos/spkr0.dat",
                                     "datos/spkr1.dat",
                                     "datos/spkr2.dat",
                                     "datos/spkr4.dat"};

    audio pzm = leerVectorAudio("datos/pzm.dat",frecuencia,profundidad,duracion);
    audio frase = subAudio(pzm,POS_SMP_TEST_DISTANCIA,QUANT_SMP_TEST_DISTANCIA);

    startPOINT = POS_SMP_TEST_DISTANCIA - 3000;
    endPOINT = QUANT_SMP_TEST_DISTANCIA + 2 * 3000;
    sala m = cargarSalaAudio(lista_archivos,frecuencia,profundidad,duracion,startPOINT,endPOINT);

    locutor spk = medirLaDistancia(m,frase,frecuencia,profundidad);
    dst_spk = get<1>(spk);

    cout << "locutor " << get<0>(spk) << endl;
    for(int i=0;i<m.size();i++){
        cout << "distancia locutor " << i << " al locutor que dijo la frase " << get<0>(spk);
        cout << ": " << dst_spk[i] << endl;
    }
    EXPECT_EQ(1,get<0>(spk));
}

/*TEST(distanciasTEST, leerSala) {
    int frecuencia, profundidad,duracion;
    vector<string> lista_archivos = {"datos/spkr0.dat",
                                     "datos/spkr1.dat",
                                     "datos/spkr5.dat"};

    sala m = cargarSalaAudio(lista_archivos,frecuencia,profundidad,duracion,10,1000);

    EXPECT_EQ(m[2].size(),1000);
}*/
