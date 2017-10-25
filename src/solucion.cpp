// Version preliminar. Esto seguramente ni compile, es para tener una idea de la complejidad de los ejercicios.

#include "ejercicios.h"
#include "Funciones_TPI.h"
#include "math.h"
#include "definiciones.h"
#include "funcionesAuxiliares.h"

/************************** EJERCICIO grabacionValida **************************/
bool grabacionValida(audio s, int prof, int freq){
    //freqvalida,enrango,profvalida,micfunciona,duramasde,
    return (freqValida(freq) && profValida(prof) && enRango(s,prof)  && micFunciona(s,freq) && duraMasDe(1.0, s, freq));

}
bool freqValida(int freq) {
    return (freq>= 4);
}
bool profValida(int prof) {
    return (prof==16 || prof == 32);
}
bool enRango(audio s, int prof) {
    int i = 0;
    int min = -pow(2,prof-1), max = pow(2,prof-1)-1;
    bool enRango = true;
    while(i < s.size()) {
        if(s[i] < min || s[i] > max) {
            enRango = false;
            break;
        }
        i++;
    }
    return enRango;
}
bool micFunciona(audio s, int freq) {
    int i = 0;
    bool funciona = true;
    while(i < s.size()) {
        int j = i+freq;
        if(sonTodosCeros(subseq(s,i,j)) && duraMasDe(1.0,subseq(s,i,j), freq)) {
            funciona = false;
            break;
        }
        i++;
    }
    return funciona;
}
float enSegundos(int n, int freq) {
    float r = ((float)n/freq);
    return r;
}
float duracion(audio s, int freq){
    return enSegundos(s.size(), freq);
}
bool duraMasDe(tiempo t, audio s, int freq) {
    return(duracion(s, freq) > t);
}
vector<int> subseq(audio s, int inicio, int fin) {
    vector<int> nueva;
    int i = inicio;
    while(i < fin) {
        nueva.push_back(s[i]);
        i++;
    }
    return nueva;
}
bool sonTodosCeros(vector<int> v) {
    int i = 0, cantCeros=0;
    while(i < v.size()) {
        if(v[i] == 0) {
            cantCeros++;
        }
        i++;
    }
    return (cantCeros==v.size());
}
int calcularIntensidadMedia(audio persona) {
    int i = 0;
    int acum = 0;
    while(i < persona.size()) {
        acum += abs(persona[i]);
        i++;
    }
    return (acum/persona.size());
}
int abs(int a) {
    int b;
    if(a<0){
        b = -a;
    }else {
        b = a;
    }
    return b;
}



/************************** EJERCICIO elAcaparador **************************/
int elAcaparador(sala m, int freq, int prof){
    //recorremos cada persona y buscamos la que tiene la max intensidad media.
    int posMax = 0, j = 1, max = calcularIntensidadMedia(m[0]);
    while(j < m.size()) {
        if(max < calcularIntensidadMedia(m[j])){
            max = calcularIntensidadMedia(m[j]);
            posMax = j;
        }
        j++;
    }
    return posMax;
}

/************************** EJERCICIO ardillizar **************************/
sala ardillizar(sala m, int prof, int freq){
    //sala res(m.size(),vector<int>(m.size()/2,0)); //inicializo mi matriz para acceder mas facil a las posiciones
    sala res;

    int i = 0;
    while(i < m.size()) {//recorro a cada persona y le saco lo que tienen en las posiciones pares
        //para ponerselo a mi nueva secuencia.
        audio vecAux;
        agregarLasPares(vecAux, m[i]);//armo un nuevo vector con los elem de las pos mares de m[i]
        res.push_back(vecAux);//meto ese vector auxiliar a mi matriz resultado
        i++;
    }
    return res;
}
void agregarLasPares(audio &res, audio mi) {//meto en sec de r(matriz) las cosas en las pos pares de m
    int i = 0;
    while(i < mi.size()) {
        if(i % 2 == 0) {
            res.push_back(mi[i]);
        }
        i++;
    }
}

/************************** EJERCICIO flashElPerezoso **************************/
sala flashElPerezoso(sala m, int prof, int freq){
    sala res(m.size(), vector<int>((2*m.size())-1,0));
    int i = 0;
    while(i < m.size()) {//recorro a cada persona para sacar sus elementos y meterlos en res
        //y ademas meter en el medio el promedio de dos elem consecutivos de m[i] (la persona)
        interPolar(res[i], m[i]);
    }

    return res;
}
int prom(int a, int b) {
    return (a+b)/2;
}
void interPolar(audio &resi, audio mi) {
    int i = 0;
    while(i < mi.size()-1) {
        //impares son elementos ficticios, pares los saco de mi
        resi[2*i] = mi[i];
        resi[(2*i)+1] = prom(mi[i], mi[i+1]);
        i++;
    }
}

/************************** EJERCICIO silencios **************************/
lista_intervalos silencios(audio s, int prof, int freq, int umbral){
    lista_intervalos res;
    return res;
}

/************************** EJERCICIO hayQuilombo **************************/
bool hayQuilombo(sala m, int prof, int freq, int umbral){
    return false;
}

/************************** EJERCICIO sacarPausas **************************/
audio sacarPausas(audio s, lista_intervalos sil, int freq, int prof, int umbral) {
    audio result;
    return result;
}

/************************** EJERCICIO encontrarAparicion **************************/
int encontrarAparicion(audio s , audio target){

    int i = 0, indiceCoincidencia = -1;
    while(i <= s.size()-target.size()) {
        if(esMaximaCorrelacion(s, i, target)) {
            indiceCoincidencia = i;
            break;
        }
        i++;
    }
    return indiceCoincidencia;
}

/************************** EJERCICIO medirLaDistancia **************************/
locutor medirLaDistancia(sala m, audio frase, int freq, int prof){
    locutor out;
    //busco el locutor que dijo la frase
    int i = 0, posMax = 0;
    float max = intensidadCorrelacion(m[0], frase);
    while(i < m.size()) {
        if(max < intensidadCorrelacion(m[i],frase)){
            max = intensidadCorrelacion(m[i], frase);
            posMax = i;
        }
        i++;
    } //aca ya consegui la posicion del locutor que dijo la frase
    get<0>(out) = posMax;
    //ahora armo la listas con las distancias al locutor
    asignarDistanciasALocutores(out,frase,m,freq);

    return out;
}

void asignarDistanciasALocutores(locutor &out, audio frase, sala m, int freq) {
    int i = 0;
    int comienzoCorrelacionLocutor = comienzoCorrelacion(m[get<0>(out)], frase);
    while(i < m.size()) {
        get<1>(out)[i] = abs((comienzoCorrelacion(m[i],frase))-(comienzoCorrelacionLocutor)) * VELOCIDAD_SONIDO / freq;
    }
}
int comienzoCorrelacion(audio personai, audio frase){
    int i = 0, acumCorrelacion = 0;
    while(i <= personai.size()-frase.size()) {
        if(esMaximaCorrelacion(personai,i,frase)) {
            acumCorrelacion+=i;
        }
        i++;
    }
}
bool esMaximaCorrelacion(audio personai, int startPoint, audio frase){
    int j = 0;
    bool esMaxima = true;
    int largo = personai.size(), largo2=frase.size();
    while(j < personai.size()-frase.size()){
        if((j != startPoint) && (correlacion(subseq(personai,j,j+frase.size()+1), frase) > correlacion(subseq(personai,startPoint,1+startPoint+frase.size()), frase))) {
            esMaxima = false;
            break;
        }
        j++;
    }
    return esMaxima;
}
float intensidadCorrelacion(audio personai, audio frase) {
    int i = 0;
    float intCor = 0;
    while(i <= personai.size()-frase.size()) {
        if(esMaximaCorrelacion(personai,i,frase)) {
            intCor += calcularIntensidadMedia(subseq(personai,i,i+frase.size()));
        }
        i++;
    }
    return intCor;
}
