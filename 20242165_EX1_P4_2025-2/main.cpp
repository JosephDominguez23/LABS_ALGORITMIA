#include <iostream>

#include "BibliotecaPila/funcionesPila.h"
#include "BibliotecaPila/Pila.h"
#define M 4
#define N 5
using namespace std;

int areaHistograma(int *altura,int columna,Pila &pila) {
    int mejor=0;
    for (int i=0;i<=columna;i++) {
        int h=(i==columna)?0:altura[i];
        while (not esPilaVacia(pila) and altura[cima(pila).numero>=h]) {
            int alto=altura[cima(pila).numero];
            desapilar(pila);
            int ancho=esPilaVacia(pila)?i:i-cima(pila).numero-1;
            if (alto*ancho>mejor) mejor=alto*ancho;
        }
        apilar(pila,{i});
    }
    while (not esPilaVacia(pila)) desapilar(pila);
    return mejor;
}

int areaMax(const int jardin[M][N],int fila,int columna) {
    int altura[N]{};
    Pila pila;
    construir(pila);
    int mejor=0;
    for (int i=0;i<fila;i++) {
        for (int j=0;j<columna;j++) {
            altura[j]=(jardin[i][j]==1)? altura[j]+1:0;
        }
        int area=areaHistograma(altura,columna,pila);
        if (area>mejor) mejor=area;
    }
    return mejor;
}

int main() {

    int jardin[M][N] = {
        {1,1,1,0,0},
        {1,1,1,1,1},
        {1,1,1,1,1},
        {1,1,0,0,0}
    };

    cout<<"La solucion sera "<<areaMax(jardin,M,N)<<endl;

    return 0;
}