#include <iostream>
using namespace std;

void imprimirMovimiento(int paquete,int origen,int destino) {
    cout<<"Mover el paquete "<<paquete<<" del almacen "
        <<(char)('A' + origen)<<" hacia el almacen "
        <<(char)('A' + destino)<<endl;
}

void mover(int paquete,int origen,int destino) {
    if (paquete==0) return;
    int diferencia=origen-destino;
    if (diferencia==2 || diferencia==-2) {
        mover(paquete-1,origen,destino);
        imprimirMovimiento(paquete,origen,1);
        mover(paquete-1,destino,origen);
        imprimirMovimiento(paquete,1,destino);
        mover(paquete-1,origen,destino);
    }
    // else {
    //     int tercero=3-origen-destino;
    //     mover(paquete-1,origen,tercero);
    //     imprimirMovimiento(paquete,origen,destino);
    //     mover(paquete-1,tercero,destino);
    // }
    //Esto se usa por si acaso se cambia el numero de destino
}

int main() {

    int paquete;
    cout<<"Ingrese la cantidad de paquetes: ";
    cin>>paquete;
    mover(paquete,0,2);

    return 0;
}