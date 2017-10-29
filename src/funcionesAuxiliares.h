
#ifndef SALADEREUNION_FUNCIONESAUXILIARES_H
#define SALADEREUNION_FUNCIONESAUXILIARES_H


bool freqValida(int freq);
bool enRango(audio s, int prof);
bool profValida(int prof);
bool micFunciona(audio a, int freq);
bool duraMasDe(tiempo t, audio s, int freq);
float duracion(audio s, int freq);
float enSegundos(int n, int freq);
int calcularIntensidadMedia(audio persona);
int abs(int a);
bool sonTodosCeros(vector<int> v);
vector<int> subseq(audio s, int inicio, int fin);
void agregarLasPares(audio &res, audio mi);
void interPolar(audio &a, audio a0);
int prom(int a, int b);
float intensidadCorrelacion(audio a, audio frase);
int comienzoCorrelacion(audio a, audio frase);
void asignarDistanciasALocutores(locutor &out, audio frase, sala m,int freq);
bool esMaximaCorrelacion(audio a, int startPoint, audio frase);
int calcularMaximaCorrelacion(audio personai, audio frase);
#endif //SALADEREUNION_FUNCIONESAUXILIARES_H
