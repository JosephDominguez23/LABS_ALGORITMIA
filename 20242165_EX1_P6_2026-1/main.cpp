#include <iostream>
#include "BibliotecaPila/Pila.h"
#include "BibliotecaPila/funcionesPila.h"
#define N 5
#define M 3
using namespace std;


void mover(Pila &origen,Pila &destino) {
    int caja=desapilar(origen).numero;
    if (not esPilaVacia(destino) and cima(destino).numero<caja) {
        cout<<"Movimiento invalido"<<endl;
    }
    apilar(destino,{caja});
}

void mover3(int n,Pila &origen,Pila &destino,Pila &aux) {
    if (n==0) return;
    mover3(n-1,origen,aux,destino);
    mover(origen,destino);
    mover3(n-1,aux,destino,origen);
}


void mover4(int n,Pila &origen,Pila &destino,Pila &x,Pila &y) {
    if (n==0) return;
    if (n==1) {
        mover(origen,destino);
        return;
    }
    mover4(n-1,origen,x,y,destino);
    mover(origen,destino);
    mover4(n-1,x,destino,origen,y);
}


void mover5(int n,Pila &origen,Pila &destino,Pila &x,Pila &y,Pila &z) {
    if (n==0) return;
    if (n==1) {
        mover(origen,destino);
        return;
    }
    mover5(n-1,origen,x,y,z,destino);
    mover(origen,destino);
    mover5(n-1,x,destino,origen,y,z);
}

int main() {

    Pila origen,aux,p1,p2,p3;
    construir(origen);
    construir(aux);
    construir(p1);
    construir(p2);
    construir(p3);
    for (int i=N;i>=1;i--) {
        apilar(origen,{i});
    }
    int rest=N;
    int k=(rest<M)?rest:M;
    mover5(k,origen,p3,aux,p1,p2);
    rest-=k;

    k=(rest<M)?rest:M;
    mover4(k,origen,p2,aux,p1);
    rest-=k;

    mover3(rest,origen,p1,aux);

    imprimir(3,p3);
    imprimir(2,p2);
    imprimir(1,p1);

    return 0;
}