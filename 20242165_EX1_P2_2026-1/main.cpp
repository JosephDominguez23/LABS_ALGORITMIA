#include <iostream>
using namespace std;

bool coincide(const char *texto, int i, const char *palabra, int j) {
    if (palabra[j]=='\0')
        return texto[i]=='\0' || texto[i]==' ';
    if (texto[i] != palabra[j]) return false;
    return coincide(texto, i+1, palabra, j+1);
}

int contar(const char *texto, const char *palabra, int i) {
    if (texto[i]=='\0') return 0;
    bool inicioPalabra=(i==0 || texto[i-1]==' ');
    int aporte=(inicioPalabra && coincide(texto, i, palabra, 0)) ? 1 : 0;
    return aporte+contar(texto, palabra, i+1);
}

int main() {
    char texto[1000], palabra[100];
    cout << "Texto: ";
    cin.getline(texto, 1000);
    cout << "Palabra: ";
    cin.getline(palabra, 100);
    cout << contar(texto, palabra, 0) << endl;
    return 0;
}