#include <iostream>
#include "BibliotecaLista/funcionesLista.h"
#include "BibliotecaLista/ElementoLista.h"
#include "BibliotecaLista/NodoLista.h"
#include "BibliotecaLista/Lista.h"
#define N 5
using namespace std;

void agregar_nodo(Lista &anillo,int id) {
    NodoLista *nuevo=new NodoLista;
    nuevo->elemento.node_id=id;
    nuevo->elemento.is_active=true;
    nuevo->skip_next=nullptr;
    if (anillo.inicio==nullptr) {
        anillo.inicio=nuevo;
        anillo.fin=nuevo;
        nuevo->next=nuevo;
    } else {
        nuevo->next=anillo.inicio;
        anillo.fin->next=nuevo;
        anillo.fin=nuevo;
    }
}

void calcular_skip_next(Lista &anillo) {
    if (esListaVacia(anillo)) return;
    NodoLista *p=anillo.inicio;
    do {
        p->skip_next=p->next->next;
        p=p->next;
    } while (p!=anillo.inicio);
}

void desactivar_nodo(Lista &anillo,int id) {
    if (esListaVacia(anillo)) return;
    NodoLista *p=anillo.inicio;
    do {
        if (p->elemento.node_id==id) {
            p->elemento.is_active=false;
            return;
        }
        p=p->next;
    } while (p!=anillo.inicio);
}

void auto_healing(Lista &anillo) {
    if (esListaVacia(anillo)) return;
    NodoLista *nuevoIni=nullptr,*p=anillo.inicio;
    do {
        if (p->elemento.is_active) {
            nuevoIni=p;
            break;
        }
        p=p->next;
    } while (p!=anillo.inicio);
    if (nuevoIni==nullptr) {
        NodoLista *q=anillo.inicio->next;
        while (q!=anillo.inicio) {
            NodoLista *r=q;
            q=q->next;
            delete r;
        }
        delete anillo.inicio;
        anillo.inicio=nullptr;
        anillo.fin=nullptr;
        return;
    }
    p=nuevoIni;
    do {
        while (not p->next->elemento.is_active) {
            NodoLista *caido=p->next;
            p->next=caido->next;
            delete caido;
        }
        p=p->next;
    } while (p!=nuevoIni);
    anillo.inicio=nuevoIni;
    p=anillo.inicio;
    while (p->next != anillo.inicio) {
        p=p->next;
    }
    anillo.fin=p;
    calcular_skip_next(anillo);
}

void imprimir(Lista anillo) {
    int cant=0;
    if (not esListaVacia(anillo)) {
        NodoLista *p=anillo.inicio;
        do {
            cant++;
            p=p->next;
        } while (p!=anillo.inicio);
    }
    cout<<"Anillo ("<<cant<<" nodos):"<<endl;
    if (esListaVacia(anillo)) return;
    NodoLista *p=anillo.inicio;
    do {
        cout<<" Nodo "<<p->elemento.node_id<<(p->elemento.is_active?"[ACTIVO]":"[CAIDO]")
            <<" siguiente="<<p->next->elemento.node_id
            <<" skip_next="<<p->skip_next->elemento.node_id<<endl;
        p=p->next;
    } while (p!=anillo.inicio);
}

void liberar(Lista &anillo) {
    if (esListaVacia(anillo)) return;
    NodoLista *p=anillo.inicio->next;
    while (p!=anillo.inicio) {
        NodoLista *q=p;
        p=p->next;
        delete q;
    }
    delete anillo.inicio;
    anillo.inicio=nullptr;
    anillo.fin=nullptr;
}


int main() {

    Lista anillo;
    construir(anillo);
    for (int i=1; i<= N; i++) {
        agregar_nodo(anillo,i*10);
    }
    calcular_skip_next(anillo);
    cout<<"=== Estado inicial ==="<<endl;
    imprimir(anillo);

    desactivar_nodo(anillo,20);
    cout << endl << ">>> Nodo 20 cae <<<" << endl;
    desactivar_nodo(anillo, 30);
    cout << endl << ">>> Nodo 30 cae <<<" << endl;

    cout << endl << "=== Estado antes de auto_healing ===" << endl;
    imprimir(anillo);

    auto_healing(anillo);
    cout<<endl<<"=== Estado despues de auto_healing ==="<<endl;
    imprimir(anillo);

    liberar(anillo);

    return 0;
}