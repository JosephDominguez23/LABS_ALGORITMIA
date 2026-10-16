//
// Created by jdomi on 15/10/2026.
//
#include <iostream>
using namespace std;
#include "Generador.h"
#include "Cola.h"
#include "funcionesCola.h"

void generarBinarios(int n) {
    Cola cola;
    construir(cola);
    encolar(cola,{1});
    for (int i = 0; i < n; i++) {
        long long x=desencolar(cola).dato;
        cout<<x<<(i<n-1?",":"");
        encolar(cola,{x*10});
        encolar(cola,{x*10+1});
    }
    cout<<endl;
}