#include <iostream>         // Biblioteca para entrada y salida estándar
#include <fstream>          // Biblioteca para operaciones de archivos
#include <vector>           // Biblioteca para utilizar el contenedor vector
#include <string>           // Biblioteca para utilizar el contenedor string
#include <algorithm>        // Biblioteca para funciones de algoritmos como transform
#include <unordered_map>    // Incluir la biblioteca  unordered_map

using namespace std;

static unordered_map<string, char> mapaAcentos = {
    {"á", 'a'}, {"é", 'e'}, {"í", 'i'},
    {"ó", 'o'}, {"ú", 'u'}, {"ü", 'u'}
};

string normalizarPalabra(const string& palabra, const unordered_map<string, char>& mapaAcentos) {
    string normalizada;
    for (char c : palabra) {
        string s(1, c);
        if (mapaAcentos.find(s) != mapaAcentos.end()) {
            normalizada += mapaAcentos.at(s);
        } else {
            normalizada += c;
        }
    }
    return normalizada;
}

bool compareCastellano(const string& a, const string& b, const string& orden) {
    unordered_map<char, int> mapaOrden;
    for (int i = 0; i < orden.size(); ++i) {
        mapaOrden[orden[i]] = i;
    }
    int len = min(a.size(), b.size());
    for (int i = 0; i < len; ++i) {
        if (mapaOrden[a[i]] != mapaOrden[b[i]]) {
            return mapaOrden[a[i]] > mapaOrden[b[i]];
        }
    }
    return a.size() > b.size();
}

int main() {
    string nombreArchivo = "palabras.txt";
    ifstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "Error al abrir el archivo " << nombreArchivo << endl;
        return 1;
    }

    vector<string> originales;
    vector<string> palabras;
    string palabra;

    while (getline(archivo, palabra)) {
        originales.push_back(palabra);
        palabras.push_back(normalizarPalabra(palabra, mapaAcentos));
    }
    
    archivo.close();

    string orden = " ABCDEFGHIJKLMNÑOPQRSTUVWXYZ";
    sort(palabras.begin(), palabras.end(), [&](const string& a, const string& b) {
        return compareCastellano(a, b, orden);
    });

    for (size_t i = 0; i < palabras.size(); ++i) {
        cout << originales[i] << " -> " << palabras[i] << endl;
    }

    return 0;
}