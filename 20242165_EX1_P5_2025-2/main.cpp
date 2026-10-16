#include <iostream>
#include <fstream>
#include <cstring>

#include "BibliotecaCola/Cola.h"
#include "BibliotecaCola/funcionesCola.h"
using namespace std;

void encolarPreferencia(Cola &cola,int codigo,int prioridad) {
    NodoCola *nuevo = new NodoCola();
    nuevo->elemento.codigo = codigo;
    nuevo->elemento.prioridad = prioridad;
    nuevo->siguiente = nullptr;
    if (esColaVacia(cola)) {
        cola.inicio=nuevo;
        cola.fin=nuevo;
        if (prioridad==1) {
            cola.list1=nuevo;
        } else {
            cola.list1=nullptr;
        }
        cola.longitud++;
        return;
    }
    if (prioridad==1) {
        if (cola.list1==nullptr) {
            nuevo->siguiente=cola.inicio;
            cola.inicio=nuevo;
            cola.list1=nuevo;
        } else {
            nuevo->siguiente=cola.list1->siguiente;
            cola.list1->siguiente=nuevo;
            if (cola.list1==cola.fin) {
                cola.fin=nuevo;
            }
            cola.list1=nuevo;
        }
    } else {
        cola.fin->siguiente=nuevo;
        cola.fin=nuevo;
    }
    cola.longitud++;
}

void atenderUno(Cola &cola,ofstream &archRep) {
    if (esColaVacia(cola)) {
        return;
    }
    NodoCola *sale=cola.inicio;
    archRep<<"Atendido: "<<sale->elemento.codigo<<" (P"
            <<sale->elemento.prioridad<<")"<<endl;
    bool eraLast1=false;
    if (sale==cola.list1) {
        eraLast1=true;
    }
    cola.inicio=cola.inicio->siguiente;
    if (cola.inicio==nullptr) {
        cola.fin=nullptr;
    }
    if (eraLast1) {
        cola.list1=nullptr;
    }
    cola.longitud--;
    delete sale;
}

void atender(Cola &cola,int k,ofstream &archRep) {
    for (int i=0;i<k;i++) {
        if (esColaVacia(cola)) {
            return;
        }
        atenderUno(cola,archRep);
    }
}

void imprimir(Cola &cola,ofstream &archRep) {
    NodoCola *p=cola.inicio;
    archRep<<"Estado: [P1:";
    bool primero = true;
    while (p!=nullptr and p->elemento.prioridad==1) {
        if (!primero) {
            archRep<<",";
        }
        archRep<<p->elemento.codigo;
        primero=false;
        p=p->siguiente;
    }
    archRep<<"][P2:";
    primero=true;
    while (p!=nullptr) {
        if (!primero) {
            archRep<<", ";
        }
        archRep<<p->elemento.codigo;
        primero=false;
        p=p->siguiente;
    }
    archRep<<"]"<<endl;
}

int main() {

    Cola cola;
    construir(cola);

    ifstream arch("eventos.txt",ios::in);
    ofstream archRep("salida.txt",ios::out);

    char comando[20];
    while (true) {
        arch>>comando;
        if (arch.eof()) break;
        if (strcmp(comando,"llegada")==0) {
            int codigo;
            char tipo[20];
            arch>>codigo>>tipo;
            if (strcmp(tipo,"preferente")==0) {
                encolarPreferencia(cola,codigo,1);
            } else {
                encolarPreferencia(cola,codigo,2);
            }
        } else if (strcmp(comando,"atender")==0) {
            int k;
            arch>>k;
            atender(cola,k,archRep);
        } else if (strcmp(comando,"imprimir")==0) {
            imprimir(cola,archRep);
        }
    }
    return 0;
}