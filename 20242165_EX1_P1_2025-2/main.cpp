#include <iostream>
#include <cmath>
#define N 13
#define A 4
using namespace std;

void generarCombinacion(int *combinacion,int numero,int n,int base) {
    int i = 0;
    for (int j = 0; j < n; j++) combinacion[j] = 0;
    while (numero != 0) {
        combinacion[i] = numero % base;
        numero = numero / base;
        i++;
    }
}

int horaFin(int alertas[N][A],int k) {
    int fin=alertas[k][2]+alertas[k][3];
    if (alertas[k][1]==1) fin++;
    return fin;
}

bool alertaValida(int alertas[N][A], int k) {
    int inicio=alertas[k][2];
    int fin=horaFin(alertas,k);
    if (inicio<8 or fin>17) return false;
    if (inicio<14 and fin>13) return false;
    return true;
}

int main() {

    int alertas[N][A] = {
        {1801, 2, 8, 1},
        {1802, 1, 8, 1},
        {1803, 1, 9, 1},
        {1804, 3, 9, 3},
        {1805, 1, 10, 1},
        {1806, 1, 11, 1},
        {1807, 3, 12, 1},
        {1808, 1, 14, 1},
        {1809, 2, 14, 2},
        {1810, 3, 14, 1},
        {1811, 2, 15, 1},
        {1812, 3, 16, 1},
        {1813, 2, 16, 2}
    };
    int estados=2;
    int maximo=pow(estados,N);
    int combinacion[N];
    int p1=1,p2=1,p3=3;
    int cant[4];
    int soluciones=0;
    bool cumple;

    // cout<<"P1, P2, P3: ";
    // cin>>p1>>p2>>p3;
    for (int i=1;i<maximo;i++) {
        generarCombinacion(combinacion,i,N,estados);
        for (int j=0;j<4;j++) {
            cant[j]=0;
        }
        for (int j=0;j<N;j++) {
            if (combinacion[j]==1) {
                cant[alertas[j][1]]++;
            }
        }
        if (cant[1]!=p1 or cant[2]!=p2 or cant[3]!=p3) continue;
        cumple=true;
        for (int j=0;j<N and cumple;j++) {
            if (combinacion[j]==0) continue;
            if (not alertaValida(alertas,j)) cumple=false;
            for (int k=j+1;k<N and cumple;k++) {
                if (combinacion[k]==1 and alertas[j][2]<horaFin(alertas,k) and
                    alertas[k][2]<horaFin(alertas,j)) {
                    cumple=false;
                }
            }
        }
        if (cumple) {
            soluciones++;
            bool primero=true;
            for (int j=0;j<N;j++) {
                if (combinacion[j]==1) {
                    if (not primero) cout<<" | ";
                    cout<<alertas[j][0]<<" P"<<alertas[j][1];
                    primero=false;
                }
            }
            cout<<endl;
        }
    }
    if (soluciones == 0) cout << "No existe combinacion que cumpla el SLA" << endl;

    return 0;
}