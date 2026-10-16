#include <iostream>
#include "BibliotecaPila/Pila.h"
#include "BibliotecaPila/funcionesPila.h"
#define MAX 100
using namespace std;

bool esValida(const char *sec) {
    Pila pila;
    construir(pila);
    for (int i=0;sec[i];i++) {
        char c=sec[i];
        if (c>='A' and c<='Z') {
            apilar(pila,{c});
        } else if (c>='a' and c<='z') {
            char mayus = c - 'a' + 'A';
            if (esPilaVacia(pila) || cima(pila).letra!=mayus) return false;
            desapilar(pila);
        } else {
            return false;
        }
    }
    return esPilaVacia(pila);
}

int main() {

    char sec[MAX];
    cout<<"Secuencia: ";
    cin>>sec;
    cout<<"Salida: "<<(esValida(sec)? "Secuencia valida":"Secuencia invalida")<<endl;

    return 0;
}