//
// Created by jdomi on 22/09/2026.
//
#include <iostream>

#include "funcionesLista.h"
#include "Lista.h"
using namespace std;
#include "Funciones.h"

#include "Lista.h"

void crear_baraja(Baraja &baraja) {
    ElementoBaraja elemento{};
    for (int i = 0; i < 53; i++) {
        if (i > 0 and i <= 13) {
            elemento= {i,'C'};
            insertarAlFinal(baraja, elemento);
        } else if (i > 13 and i <= 26) {
            elemento = {i-13,'D'};
            insertarAlFinal(baraja, elemento);
        } else if (i > 26 and i <= 39) {
            elemento = {i-26,'T'};
            insertarAlFinal(baraja, elemento);
        } else if (i > 39) {
            elemento = {i-39,'E'};
            insertarAlFinal(baraja, elemento);
        }
    }
}

NodoBaraja *extraer_en_posicion(Baraja &baraja,int posicion) {
    NodoBaraja *recorrido = baraja.inicio;
    NodoBaraja *anterior = nullptr;
    NodoBaraja *encontrado = nullptr;
    int auxContador = 0;
    while (recorrido != nullptr) {
        if (posicion == auxContador) {
            if (anterior == nullptr) {
                baraja.inicio = recorrido->siguiente;
            } else {
                anterior -> siguiente = recorrido->siguiente;
            }
            if (recorrido == baraja.fin) {
                baraja.fin = anterior;
            }
            recorrido -> siguiente = nullptr;
            baraja.longitud--;
            encontrado = recorrido;
            return encontrado;
        }
        anterior = recorrido;
        auxContador++;
        recorrido = recorrido->siguiente;
    }
    return encontrado;
}

void barajar(Baraja &baraja) {
    srand(time(nullptr));
    int auxContador = 0;
    while ((52 - auxContador) > 0) {
        int posicion = rand()%(52 - auxContador);
        NodoBaraja *extraido = extraer_en_posicion(baraja,posicion);
        insertarNodoAlFinal(baraja, extraido);
        auxContador++;
    }
}

void insertarNodoAlFinal(Baraja &baraja,NodoBaraja *&extraido) {
    if (esListaVacia(baraja)) {
        baraja.inicio = extraido;
        baraja.fin =  extraido;
    } else {
        baraja.fin -> siguiente = extraido;
        baraja.fin = extraido;
    }
    baraja.longitud++;
}

void imprimirCar(char car,int n) {
    for (int i = 0; i < n; i++) {
        cout << car;
    }
    cout << endl;
}
