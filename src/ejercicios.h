#ifndef SALADEREUNION_EJERCICIOS_H
#define SALADEREUNION_EJERCICIOS_H

#include <iostream>
#include <vector>
#include <math.h>
#include <tuple>
#include "definiciones.h"

using namespace std;

bool grabacionValida(audio s, int prof, int freq);
int elAcaparador(sala m, int freq, int prof);
sala ardillizar(sala m, int prof, int freq);
sala flashElPerezoso(sala m, int prof, int freq);
lista_intervalos silencios(audio s, int prof, int freq, int umbral);
bool hayQuilombo(sala m, int prof, int freq, int umbral);
locutor medirLaDistancia(sala m, audio frase, int freq, int prof);
int encontrarAparicion(audio target , audio s);
float compararSilencios(audio vec, int freq, int prof, int locutor, int umbralSilencio);
float resultadoFinal(sala m, int freq, int prof, int umbralSilencio);
locutor medirLaDistancia(sala m, audio frase, int freq, int prof);
int encontrarMejorUmbralFuerzaBruta(sala m, int freq, int prof);
audio sinSilencios(audio s, lista_intervalos sil, int freq, int prof, int umbral);

#endif //SALADEREUNION_EJERCICIOS_H