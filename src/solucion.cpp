// Version preliminar. Esto seguramente ni compile, es para tener una idea de la complejidad de los ejercicios.

#include "ejercicios.h"
#include "Funciones_TPI.h"
#include <algorithm>
#include "math.h"
#include "definiciones.h"
#include "funcionesAuxiliares.h"

/************************** EJERCICIO grabacionValida **************************/
bool grabacionValida(audio s, int prof, int freq) {
    return (freqValida(freq) && profValida(prof) && enRango(s, prof) && micFunciona(s, freq) &&
            duraMasDe(1.0, s, freq));
}

bool freqValida(int freq) {
    return (freq >= 4);
}

bool profValida(int prof) {
    return (prof == 16 || prof == 32);
}

bool enRango(audio s, int prof) {
    int i = 0;

    int min = (int) -pow(2, prof - 1), max = (int) pow(2, prof - 1) - 1;
    bool enRango = true;

    while (i < s.size()) {
        if (s[i] < min || s[i] > max) {
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
    while (i < s.size() - freq) {
        if (sonTodosCeros(subseq(s, i, i + freq + 1))) {
            funciona = false;
            break;
        }
        i++;
    }
    /*
    while(i < s.size()) {
        int j = i+freq;
        if(sonTodosCeros(subseq(s,i,j))) {
            funciona = false;
            break;
        }
        i++;
    }*/
    return funciona;
}

float enSegundos(int n, int freq) {
    float r = ((float) n / freq);
    return r;
}

float duracion(audio s, int freq) {
    return enSegundos(s.size(), freq);
}

bool duraMasDe(tiempo t, audio s, int freq) {
    return (duracion(s, freq) > t);
}

vector<int> subseq(audio s, int inicio, int fin) {
    vector<int> nueva;
    int i = inicio;

    while (i < fin) {
        nueva.push_back(s[i]);
        i++;
    }
    return nueva;
}

bool sonTodosCeros(vector<int> v) {
    int i = 0, cantCeros = 0;
    while (i < v.size()) {
        if (v[i] == 0) {
            cantCeros++;
        }
        i++;
    }
    return (cantCeros == v.size());
}
/************************** FIN EJERCICIO grabacionValida **************************/

/************************** EJERCICIO elAcaparador **************************/
int elAcaparador(sala m, int freq, int prof) {
    int posMax = 0, j = 1, max = calcularIntensidadMedia(m[0]);
    while (j < m.size()) {
        if (max < calcularIntensidadMedia(m[j])) {
            max = calcularIntensidadMedia(m[j]);
            posMax = j;
        }
        j++;
    }
    return posMax;
}

/************************** FIN EJERCICIO elAcaparador **************************/
int calcularIntensidadMedia(audio persona) {
    int i = 0;
    int acum = 0;

    while (i < persona.size()) {
        acum += abs(persona[i]);
        i++;
    }

    return (acum / persona.size());
}
/************************** EJERCICIO ardillizar **************************/

sala ardillizar(sala m, int prof, int freq) {
    sala res;
    int i = 0;
    while (i < m.size()) {
        //recorro a cada persona y le saco lo que tienen en las posiciones pares
        //para ponerselo a mi nueva secuencia.
        audio vecAux;
        agregarLasPares(vecAux, m[i]);//armo el audio ardillizado de la persona i
        res.push_back(vecAux);//agrego ese audio a la sala de personas
        i++;
    }

    return res;
}
void agregarLasPares(audio &res, audio mi) {
    int i = 0;
    while (i < mi.size()) {
        if (i % 2 == 0) {
            res.push_back(mi[i]);
        }
        i++;
    }
}
/************************** FIN EJERCICIO ardillizar **************************/

/************************** EJERCICIO flashElPerezoso **************************/
sala flashElPerezoso(sala m, int prof, int freq) {
    int l = (2 * m[0].size()) - 1;
    sala res(m.size(), vector<int>(l, 0));
    int i = 0;
    while (i < m.size()) {
        //recorro a cada persona para sacar sus elementos y meterlos en res
        //y ademas meter en el medio el promedio de dos elem consecutivos de m[i]
        interPolar(res[i], m[i]);
        i++;
    }

    return res;
}
int prom(int a, int b) {
    return (int) ((a + b) / 2);
}
void interPolar(audio &resi, audio mi) {
    int i = 0;
    /*while(i < mi.size()) {
        resi[2*i] = mi[i];
        i++;
    }
    i=0;*/
    while (i < mi.size() - 1) {
        resi[2 * i] = mi[i];
        resi[(2 * i) + 1] = prom(mi[i], mi[i + 1]);
        i++;
    }
    resi[2 * mi.size() - 2] = mi[mi.size() - 1];
}
/************************** FIN EJERCICIO flashElPerezoso **************************/

/************************** EJERCICIO silencios **************************/
lista_intervalos silencios(audio s, int prof, int freq, int umbral) {
    lista_intervalos res;
    tiempo tiempoMinimo = 0.1;
    int indicesMinimos = (int)(tiempoMinimo * freq);
    int x = 0;
    while (x < s.size() - indicesMinimos) {
        float end = -1;
        for (int y = x; y < s.size(); y++) {
            if (abs(s[y]) < umbral) {
                if (y - x >= indicesMinimos) {
                    if (y == s.size() - 1) {
                        end = float(y) / freq;
                        break;
                    }
                    // Es y+1 porque el silencio cuenta hasta exactamente el instante en que supera el umbral porque asi lo dice el caso de ejemplo dado
                    end = float(y + 1) / freq;
                }
            } else {
                break;
            }
        }
        if (end != -1) {
            res.push_back(make_tuple(float(x) / freq, end));
            x = int(end * freq);
        }
        x++;
    }

    return res;
}
/************************** FIN EJERCICIO silencios **************************/

/************************** EJERCICIO hayQuilombo **************************/
bool estaEnSilencio(audio a, int pos, int prof, int freq, int umbral) {
    lista_intervalos s = silencios(a, prof, freq, umbral);
    for (int x = 0; x < s.size(); x++) {
        // Si s1 <= pos < s2 donde s1 y s2 son las posiciones correspondientes a los tiempos obtenidos en la funcion anterior
        if (round(get<0>(s[x]) * freq) <= pos &&
            ((pos < round(get<1>(s[x]) * freq)) || (pos == a.size() - 1 && pos == round(get<1>(s[x]) * freq)))) {
            return true;
        }
    }
    return false;
}
bool hayQuilombo(sala m, int prof, int freq, int umbral) {
    bool hayQuilombo = false;
    for (int x = 0; x < m.size() - 1; x++) {
        for (int y = x + 1; y < m.size(); y++) {
            for (int z = 0; z < m[x].size(); z++) {
                if (!(estaEnSilencio(m[x], z, prof, freq, umbral) || estaEnSilencio(m[y], z, prof, freq, umbral))) {
                    hayQuilombo = true;
                }
            }
        }
    }
    return hayQuilombo;
}
/************************** FIN EJERCICIO hayQuilombo **************************/

/************************** EJERCICIO sinSilencios **************************/

audio sinSilencios(audio vec, vector<intervalo> listaDeSilencios, int freq, int prof, int umbral) {
    audio audioSinSilencios;
    //Obtenemos los silencios del audio pasado
    //vector<intervalo> listaDeSilencios = silencios(vec, prof, freq, umbral);
    int i = 0;
    while (i < vec.size()) {
        if (!estaEnSilencio(vec, i, prof, freq, umbral)) {
            audioSinSilencios.push_back(vec[i]);
        }
        i++;
    }
    return audioSinSilencios;
}
/************************** FIN EJERCICIO sinSilencios **************************/

/************************** EJERCICIO encontrarAparicion **************************/
int encontrarAparicion(audio x, audio y) {
    return calcularMaximaCorrelacion(x, y);
}

int calcularMaximaCorrelacion(audio personai, audio frase) {
    int i = 0, posMax = i;
    float temp;
    float maxCor = correlacion(subseq(personai, i, i + frase.size() + 1), frase);
    vector<vector<int> > subsecuencias(personai.size() - frase.size() + 1, vector<int>(frase.size(), 0));
    int x = 0;
    while (x < personai.size()) {
        for (int y = max(0, x - int(frase.size()) + 1); y < min(int(subsecuencias.size()), x + 1); y++) {
            subsecuencias[y][x - y] = personai[x];
        }
        x++;
    }
    while (i < personai.size() - frase.size()) {
        temp = correlacion(subsecuencias[i], frase);
        if (maxCor < temp) {
            maxCor = temp;
            posMax = i;
        }
        i++;
    }
    return posMax;
}
/************************** FIN EJERCICIO encontrarAparicion **************************/


/************************** EJERCICIO enmascarar **************************/
vector<bool> enmascarar(lista_intervalos ints, float duracion) {
    vector<bool> res(int(100 * duracion), false);
    for (int x = 0; x < ints.size(); x++) {
        int cota = ((ceil(get<1>(ints[x]) * 100)) < res.size()) ? (ceil(get<1>(ints[x]) * 100)) : res.size();
        for (int y = ceil(get<0>(ints[x]) * 100); y < cota; y++) {
            res[y] = true;
        }
    }
    return res;
}
/************************** FIN EJERCICIO enmascarar **************************/


/************************** EJERCICIO negacionLogica **************************/
vector<bool> negacionLogica(vector<bool> mascara) {
    for (int x = 0; x < mascara.size(); x++) {
        mascara[x] = !mascara[x];
    }
    return mascara;
}
/************************** FIN EJERCICIO negacionLogica **************************/


/*********************** EJERCICIO compararSilencios ************************/
lista_intervalos leerIntervalosDeHabla(int locutor) {
    ifstream lector;
    lector.open("datos/habla_spkr" + to_string(locutor) + ".txt");
    lista_intervalos intervalos;
    while (!lector.eof()) {
        intervalo act;
        lector >> get<0>(act) >> get<1>(act);
        if (!(get<0>(act) == 0 && get<1>(act) == 0)) { // Verificacion por ultima linea en blanco
            intervalos.push_back(act);
        }
    }
    lector.close();
    return intervalos;
}

float compararSilencios(audio vec, int freq, int prof, int locutor, int umbralSilencio) {
    lista_intervalos intervalos = leerIntervalosDeHabla(locutor);
    vector<bool> mascara = enmascarar(intervalos, float(vec.size()) / freq);
    vector<bool> silenciosXarchivo = negacionLogica(mascara);
    lista_intervalos sil = silencios(vec, prof, freq, umbralSilencio);
    vector<bool> silenciosXfuncion = enmascarar(sil, float(vec.size()) / freq);

    int vp = 0, vn = 0, fp = 0, fn = 0;
    for (int x = 0; x < silenciosXfuncion.size(); x++) {
        if (silenciosXfuncion[x]) {
            if (silenciosXarchivo[x]) {
                vp++;
            } else {
                fp++;
            }
        } else {
            if (silenciosXarchivo[x]) {
                fn++;
            } else {
                vn++;
            }
        }
    }
    float precision = vp + fp > 0 ? float(vp) / (vp + fp) : 0;
    float recall = vp + fn > 0 ? float(vp) / (vp + fn) : 0;
    //cout << vp << ", " << fp << ", " << vn << ", " << fn << endl;
    float F1 = precision + recall > 0 ? 2 * ((precision * recall) / (precision + recall)) : 0;
    return F1;
}
/*********************** EJERCICIO FIN compararSilencios ************************/


/************************** EJERCICIO umbral/resultadoFinal **************************/
float resultadoFinal(sala m, int freq, int prof, int umbralSilencio) {
    float suma = 0;
    for (int x = 0; x < m.size(); x++) {
        float act = compararSilencios(m[x], freq, prof, x, umbralSilencio);
        //cout << act << ", " << x << ", " << umbralSilencio << endl;
        suma += act;
    }
    return suma / m.size();
}

int encontrarMejorUmbralFuerzaBruta(sala m, int freq, int prof) {
    int maximo = 0;
    for (int x = 0; x < m.size(); x++) {
        maximo = max(maximo, *max_element(begin(m[x]), end(m[x])));
    }
    cout << maximo << endl;
    pair<int, float> mejorUmbral = {-1, 0}; // Actual mejor, Puntaje del actual mejor
    for (int x = 0; x <= maximo; x += maximo / 10) {
        float act = resultadoFinal(m, freq, prof, x);
        if (mejorUmbral.first == -1 || mejorUmbral.second < act) {
            mejorUmbral.first = x;
            mejorUmbral.second = act;
        }
        cout << "Umbral: " << x << " F1: " << act << endl;
    }
    cout << "Mejor umbral: " << mejorUmbral.first << " con F1: " << mejorUmbral.second << endl;
}
/************************** FIN EJERCICIO umbral/resultadoFinal **************************/


/************************** EJERCICIO medirLaDistancia **************************/
locutor medirLaDistancia(sala m, audio frase, int freq, int prof) {
    locutor out;
    //busco el locutor que dijo la frase
    int i = 0, posMax = 0;
    float max = intensidadCorrelacion(m[i], frase);

    while (i < m.size()) {
        float intensidad = intensidadCorrelacion(m[i], frase);
        if (max < intensidad) {
            max = intensidad;
            posMax = i;
        }
        i++;
    }

    //aca ya consegui la posicion del locutor que dijo la frase
    get<0>(out) = posMax;
    //ahora armo la listas con las distancias al locutor
    asignarDistanciasALocutores(out, frase, m, freq);

    return out;
}

void asignarDistanciasALocutores(locutor &out, audio frase, sala m, int freq) {
    int i = 0;
    int comienzoCorrelacionLocutorDijoFrase = comienzoCorrelacion(m[get<0>(out)], frase);
    while (i < m.size()) {
        get<1>(out).push_back(
                abs((comienzoCorrelacion(m[i], frase)) - (comienzoCorrelacionLocutorDijoFrase)) * VELOCIDAD_SONIDO /
                freq);
        i++;
    }
}

int comienzoCorrelacion(audio personai, audio frase) {
    return calcularMaximaCorrelacion(personai, frase);
}

float intensidadCorrelacion(audio personai, audio frase) {
    int p = calcularMaximaCorrelacion(personai, frase);
    return calcularIntensidadMedia(subseq(personai, p, p + 1 + frase.size()));
}
/************************** FIN EJERCICIO medirLaDistancia **************************/
