#include <iostream>
using namespace std;

#define F 5
#define C 6
#define H 3
#define W 2
#define U 80

void imprimirMatriz(int matriz[F][C]) {
    for (int i = 0; i < F; i++) {
        for (int j = 0; j < C; j++)
            cout << matriz[i][j] << " ";
        cout << endl;
    }
}

int sumaBloque(int matriz[F][C],int fi,int ci,int ff,int cf) {
    int suma=0;
    for (int i=fi;i<=ff;i++) {
        for (int j=ci;j<=cf;j++) {
            suma+=matriz[i][j];
        }
    }
    return suma;
}

void buscarbloques(int matriz[F][C],int fila,int columna,int alMax,
    int anchMax,int umbral) {
    int cont=0;
    for (int i=0;i<fila;i++) {
        for (int k=0;k<columna;k++) {
            for (int h=0;h<alMax and i+h<fila;h++) {
                for (int w=0;w<anchMax and k+w<columna;w++) {
                    int ff=i+h,cf=k+w;
                    int suma=sumaBloque(matriz,i,k,ff,cf);
                    if (suma>umbral) {
                        cont++;
                        cout << "Bloque sospechoso " << cont << ":" << endl;
                        cout << "Fila inicial: " << i << endl;
                        cout << "Columna inicial: " << k << endl;
                        cout << "Fila final: " << ff << endl;
                        cout << "Columna final: " << cf << endl;
                        cout << "Suma: " << suma << endl;
                    }
                }
            }
        }
    }
    if (cont == 0) cout << "No se encontraron patrones sospechosos" << endl;
}


int main() {

    int matriz[F][C] = {
        {4,1,3,2,5,1},
        {10,35,2,1,4,3},
        {8,30,5,2,6,4},
        {1,25,20,3,2,1},
        {2,1,15,40,3,2}};
    cout<<"Matriz evaluada"<<endl;
    imprimirMatriz(matriz);
    cout << "Altura maxima del bloque: " << H << endl;
    cout << "Ancho maximo del bloque: " << W << endl;
    cout << "Umbral sospechoso: " << U << endl;
    buscarbloques(matriz,F,C,H,W,U);

    return 0;
}