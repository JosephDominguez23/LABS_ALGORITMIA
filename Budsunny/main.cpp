#include <iostream>
#include <iomanip>
#include "BibliotecaPila/funcionesPila.h"
#include "BibliotecaPila/Pila.h"
#include "BibliotecaPila/ElementoPila.h"
using namespace std;

void cerrarTramo(Pila &pila,int frecTramo,int &maxFrec,int &maxDur) {
    int duracion=0;
    while (not esPilaVacia(pila)) {
        desapilar(pila);
        duracion++;
    }
    if (duracion>maxDur or (duracion==maxDur and frecTramo>maxFrec)) {
        maxDur = duracion;
        maxFrec = frecTramo;
    }
}

void corregirFrecuencias(int *frecuencias,int n,int &maxFrec,int &maxDur) {
    Pila pila;
    construir(pila);
    maxFrec=-1;
    maxDur=0;
    int actual=0;
    for (int i=0;i<n;i++) {
        if (not esPilaVacia(pila) and actual!=frecuencias[i])
            cerrarTramo(pila,actual,maxFrec,maxDur);
        apilar(pila,{frecuencias[i]});
        actual=frecuencias[i];
    }
    if (not esPilaVacia(pila))
        cerrarTramo(pila,actual,maxFrec,maxDur);
}


int main() {

    int frecuencias[]={1,2,1,4,4,4,4,4,2,2,1};
    // int frecuencias[]={1,2,1,4,5,6,4,5,2,2,1};
    int n=sizeof(frecuencias)/sizeof(frecuencias[0]);
    int maxFrec,maxDur;

    corregirFrecuencias(frecuencias,n,maxFrec,maxDur);

    cout << "Frecuencia maxima=" << maxFrec << "   Duracion=" << maxDur << endl;

    return 0;
}