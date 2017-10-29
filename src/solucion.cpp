// Version preliminar. Esto seguramente ni compile, es para tener una idea de la complejidad de los ejercicios.

#include "ejercicios.h"
#include "Funciones_TPI.h"
#include "math.h"
#include "definiciones.h"
#include "funcionesAuxiliares.h"

/************************** EJERCICIO grabacionValida **************************/
bool grabacionValida(audio s, int prof, int freq){
    //freqvalida,enrango,profvalida,micfunciona,duramasde,
    return (freqValida(freq) && profValida(prof) && enRango(s,prof)  && micFunciona(s, freq) && duraMasDe(1.0, s, freq));
}

bool freqValida(int freq) {
    return (freq >= 4);
}

bool profValida(int prof) {
    return (prof == 16 || prof == 32);
}

bool enRango(audio s, int prof) {
    int i = 0;
    //int min = -pow(2,prof-1), max = pow(2,prof-1)-1;
    int min = (int) -pow(2,prof-1), max = (int) pow(2,prof-1)-1;
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
    float r = ((float) n/freq);
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
    int i = 0, cantCeros = 0;

    while(i < v.size()) {
        if(v[i] == 0) {
            cantCeros++;
        }
        i++;
    }

    return (cantCeros == v.size());
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
    }
    else{
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

    while(i < m.size()) {
        //recorro a cada persona y le saco lo que tienen en las posiciones pares
        //para ponerselo a mi nueva secuencia.
        audio vecAux;
        agregarLasPares(vecAux, m[i]);//armo un nuevo vector con los elem de las pos mares de m[i]
        res.push_back(vecAux);//meto ese vector auxiliar a mi matriz resultado
        i++;
    }

    return res;
}

void agregarLasPares(audio &res, audio mi) {
    //meto en sec de r(matriz) las cosas en las pos pares de m
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
/*/
lista_intervalos silencios(audio s, int prof, int freq, int umbral){
    lista_intervalos res;

    const int indicesMinimos = floor(0.1 * freq);
    for (int x = 0; x < s.size() - indicesMinimos; x++){
        //intervalo silencioActual = {float(x)/freq, -1};
        intervalo silencioActual = std::make_tuple(float(x)/freq, -1);
        for (int y = x; y < s.size(); y++){
            if (abs(s[y]) < umbral){
                if (y - x >= indicesMinimos){
                    // Es y+1 porque el silencio cuenta hasta exactamente el instante en que supera el umbral porque asi lo dice el caso de ejemplo dado
                    get<1>(silencioActual) = float(y+1)/freq;
                }
            }else{
                break;
            }
        }
        if (get<1>(silencioActual) != -1){
            res.push_back(silencioActual);
            x = int(get<1>(silencioActual) * freq);
        }
    }

    return res;
}
//*/
//lista_intervalos silencios(audio s, int prof, int freq, int umbral, float tiempoMinimo){
lista_intervalos silencios(audio s, int prof, int freq, int umbral){
    lista_intervalos res;

    tiempo tiempoMinimo = 0.1;

    int indicesMinimos = int(tiempoMinimo * freq);
    int x = 0;

    while( x < s.size() - indicesMinimos){
        float end = -1;
        for (int y = x; y < s.size(); y++){
            if (abs(s[y]) < umbral){
                if (y - x >= indicesMinimos){
                    if (y == s.size()-1){
                        end = float(y)/freq;
                        break;
                    }
                    // Es y+1 porque el silencio cuenta hasta exactamente el instante en que supera el umbral porque asi lo dice el caso de ejemplo dado
                    end = float(y+1)/freq;
                }
            }else{
                break;
            }
        }
        if (end != -1){
            res.push_back(make_tuple(float(x)/freq,end));
            x = int(end * freq);
        }
        x++;
    }

    return res;
}

/************************** EJERCICIO hayQuilombo **************************/
bool estaEnSilencio(audio a, int pos, int prof, int freq, int umbral){
    lista_intervalos s = silencios(a,prof,freq,umbral);
    for (int x = 0; x < s.size(); x++){
        //printf("sil0: %f, sil1: %f, freq: %i, pos: %i\n", get<0>(s[x]), get<1>(s[x]), freq, pos);
        if (get<0>(s[x]) * freq <= pos && pos < get<1>(s[x]) * freq) { // Si s1 <= pos < s2 donde s1 y s2 son las posiciones correspondientes a los tiempos obtenidos en la funcion anterior
            return true;
        }
    }
    return false;
}

bool hayQuilombo(sala m, int prof, int freq, int umbral){
    for (int x = 0; x < m.size()-1; x++){
        for (int y = x+1; y  < m.size(); y++){
            for (int z = 0; z < m[x].size(); z++) {
                if (!(estaEnSilencio(m[x], z, prof, freq, umbral) || estaEnSilencio(m[y], z, prof, freq, umbral))) {
                    //printf("x: %i, y: %i, z: %i, resx: %i, resy: %i\n", x, y, z, estaEnSilencio(m[x], z, prof, freq, umbral), estaEnSilencio(m[y], z, prof, freq, umbral));
                    return true;
                }
            }
        }
    }
    return false;
}
/************************** EJERCICIO sacarPausas **************************/
audio sacarPausas(audio s, lista_intervalos sil, int freq, int prof, int umbral) {
    audio result;
    return result;
}

/************************** EJERCICIO encontrarAparicion **************************/
int encontrarAparicion(audio s , audio target){
    return calcularMaximaCorrelacion(s,target);
}

int calcularMaximaCorrelacion(audio personai, audio frase) {
    int i = 0, posMax = i;
    float temp;
    float maxCor = correlacion(subseq(personai, i,i+frase.size()+1),frase);
    while(i < personai.size()-frase.size()) {
        temp = correlacion(subseq(personai, i,i+frase.size()+1),frase);
        if(maxCor < temp) {
            maxCor = temp;
            posMax = i;
        }
        i++;
    }
    return posMax;
}

bool esMaximaCorrelacion(audio personai, int startPoint, audio frase){
    //int j = startPoint+1;
    int maxCor = calcularMaximaCorrelacion(personai,frase);
    /*int largo = personai.size(), largo2=frase.size();
    while(j < largo-largo2){
        cout << "AHORA j VALE: " << j<<endl;
        if((correlacion(subseq(personai,j,j+largo2+1), frase) > correlacion(subseq(personai,startPoint,1+startPoint+largo2), frase))) {
            esMaxima = false;
            break;
        }
        j++;
    }*/
    return (correlacion(subseq(personai,maxCor,frase.size()+1+maxCor),frase) == correlacion(subseq(personai,startPoint,startPoint+frase.size()+1), frase));
}

/************************** EJERCICIO medirLaDistancia **************************/
locutor medirLaDistancia(sala m, audio frase, int freq, int prof){
    locutor out;
    //busco el locutor que dijo la frase
    int i = 0, posMax = 0;
    float max = intensidadCorrelacion(m[i], frase);

    while(i < m.size()) {
        float intensidad = intensidadCorrelacion(m[i],frase);
        if(max < intensidad){
            max = intensidad;
            posMax = i;
        }
        i++;
    }

    //aca ya consegui la posicion del locutor que dijo la frase
    get<0>(out) = posMax;
    //ahora armo la listas con las distancias al locutor
    asignarDistanciasALocutores(out,frase,m,freq);

    return out;
}

void asignarDistanciasALocutores(locutor &out, audio frase, sala m, int freq) {
    int i = 0;
    int comienzoCorrelacionLocutorDijoFrase = comienzoCorrelacion(m[get<0>(out)], frase);
    while(i < m.size()) {
        get<1>(out).push_back(abs((comienzoCorrelacion(m[i],frase))-(comienzoCorrelacionLocutorDijoFrase)) * VELOCIDAD_SONIDO / freq);
        i++;
        cout << "YA ORDENE PERSONA : " << i << " y faltan " << m.size()-i<<endl;
    }
}

int comienzoCorrelacion(audio personai, audio frase){
    /*int i = 0, acumCorrelacion = 0;
    while(i < personai.size()-frase.size()) {
        if(esMaximaCorrelacion(personai,i,frase)) {
            acumCorrelacion+=i;
            break;
        }
        i++;
    }*/
    return calcularMaximaCorrelacion(personai, frase);
}

float intensidadCorrelacion(audio personai, audio frase) {
    /*int i = 0;
    float intCor = 0;
    while(i < personai.size()-frase.size()) {
        int m = calcularMaximaCorrelacion(personai, frase);
        if(esMaximaCorrelacion(personai,i,frase)) {
            intCor += calcularIntensidadMedia(subseq(personai,i,i+frase.size()));
            break;
        }
        i++;
    }*/
    int p = calcularMaximaCorrelacion(personai, frase);
    return calcularIntensidadMedia(subseq(personai,p,p+1+frase.size()));
}

/************************** EJERCICIO sinSilencios **************************/

//bool indicePerteneceASilencio(int indice, vector<intervalo> listaDeSilencios, int freq);

audio sinSilencios (audio vec , vector<intervalo> listaDeSilencios, int freq , int prof, int umbral){
    audio audioSinSilencios;

    //Obtenemos los silencios del audio pasado
    //vector<intervalo> listaDeSilencios = silencios(vec, prof, freq, umbral);

    int i = 0;

    while(i < vec.size()){
        //*/
        if(!indicePerteneceASilencio(i, listaDeSilencios, freq)){
            audioSinSilencios.push_back(vec[i]);
        }
        //*/

        /*/
        if(!estaEnSilencio(vec, i, prof, freq, umbral)){
            audioSinSilencios.push_back(vec[i]);
        }
        //*/

        i++;
    }

    return audioSinSilencios;
}

bool indicePerteneceASilencio(int indice, vector<intervalo> listaDeSilencios, int freq){
    bool pertenece = false;

    int cont = 0;

    while(cont < listaDeSilencios.size()){
        if(indice >= (get<0>(listaDeSilencios[cont]) * freq) && indice < (get<1>(listaDeSilencios[cont]) * freq)){
            pertenece = true;
            break;
        }

        cont++;
    }

    return pertenece;
}