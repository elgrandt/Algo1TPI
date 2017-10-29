
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
<<<<<<< HEAD
bool sonTodosCeros(vector<int>v);
=======
bool sonTodosCeros(vector<int> v);
>>>>>>> master
vector<int> subseq(audio s, int inicio, int fin);
void agregarLasPares(audio &res, audio mi);
void interPolar(audio &a, audio a0);
int prom(int a, int b);
float intensidadCorrelacion(audio a, audio frase);
int comienzoCorrelacion(audio a, audio frase);
void asignarDistanciasALocutores(locutor &out, audio frase, sala m,int freq);
<<<<<<< HEAD
bool esMaximaCorrelacion(audio a, int startPoint, audio frase);
int calcularMaximaCorrelacion(audio personai, audio frase);
=======
bool esMaximaCorrelacion(audio a, int startPoint, audio frase);//no la estoy usando
int calcularMaximaCorrelacion(audio personai, audio frase);
bool indicePerteneceASilencio(int indice, vector<intervalo> listaDeSilencios, int freq);
>>>>>>> master
#endif //SALADEREUNION_FUNCIONESAUXILIARES_H
