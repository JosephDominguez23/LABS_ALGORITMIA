#include <iostream>
#define N 5
using namespace std;

struct Nodo {
    int id;
    char tipo;
    Nodo *sig;
};

// Agrega el nodo n al final de la lista (ini, fin)
void agregarAlFinal(Nodo *&ini, Nodo *&fin, Nodo *n) {
    n->sig = nullptr;
    if (ini == nullptr) ini = fin = n;
    else { fin->sig = n; fin = n; }
}

// Quita el primer nodo de la sublista (ini) y lo agrega a la lista resultado
void pasarPrimero(Nodo *&ini, Nodo *&iniRes, Nodo *&finRes) {
    if (ini == nullptr) return;
    Nodo *n = ini;
    ini = ini->sig;
    agregarAlFinal(iniRes, finRes, n);
}

Nodo *reordenaLista(Nodo *cabeza) {
    Nodo *iniA = nullptr, *finA = nullptr;
    Nodo *iniB = nullptr, *finB = nullptr;
    Nodo *iniC = nullptr, *finC = nullptr;

    while (cabeza != nullptr) {                     // 1) separar por tipo
        Nodo *sig = cabeza->sig;
        if (cabeza->tipo == 'A') agregarAlFinal(iniA, finA, cabeza);
        else if (cabeza->tipo == 'B') agregarAlFinal(iniB, finB, cabeza);
        else agregarAlFinal(iniC, finC, cabeza);
        cabeza = sig;
    }

    Nodo *iniRes = nullptr, *finRes = nullptr;      // 2) intercalar A, B, C
    while (iniA != nullptr || iniB != nullptr || iniC != nullptr) {
        pasarPrimero(iniA, iniRes, finRes);
        pasarPrimero(iniB, iniRes, finRes);
        pasarPrimero(iniC, iniRes, finRes);
    }
    return iniRes;
}

void imprimir(Nodo *p) {
    cout << "[";
    for (; p != nullptr; p = p->sig) {
        cout << "(" << p->id << "," << p->tipo << ")";
        if (p->sig != nullptr) cout << " -> ";
    }
    cout << "]" << endl;
}

int main() {
    int n;
    cout << "Cantidad de ordenes: ";
    cin >> n;
    Nodo *cabeza = nullptr, *cola = nullptr;
    for (int i = 0; i < n; i++) {
        Nodo *nuevo = new Nodo;
        cin >> nuevo->id >> nuevo->tipo;
        agregarAlFinal(cabeza, cola, nuevo);
    }
    cout << "Entrada: ";
    imprimir(cabeza);
    cabeza = reordenaLista(cabeza);
    cout << "Salida: ";
    imprimir(cabeza);
    while (cabeza != nullptr) {
        Nodo *t = cabeza;
        cabeza = cabeza->sig;
        delete t;
    }
    return 0;
}