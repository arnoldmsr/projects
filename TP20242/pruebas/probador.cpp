#include <iostream>         // Biblioteca para entrada y salida estándar
#include <fstream>          // Biblioteca para operaciones de archivos
#include <vector>           // Biblioteca para utilizar el contenedor vector
#include <string>           // Biblioteca para utilizar el contenedor string
#include <algorithm>        // Biblioteca para funciones de algoritmos como transform
#include <map>              // Incluir la biblioteca map

using namespace std;

map<char, int> crearMapa() {
    map<char, int> mapa;
    string caracteres = "AaÁáBbCcDdEeÉéFfGgHhIiÍíJjKkLlMmNnÑñOoÓóPpQqRrSsTtUuÚúVvWwXxYyZz";
    for (int i = 0; i < caracteres.size(); ++i) {
        mapa[caracteres[i]] = i;
    }
    return mapa; 
}

// Función para leer las palabras desde el archivo
vector<string> leerArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    vector<string> palabras;
    string palabra;

    if (archivo.is_open()) {
        while (getline(archivo, palabra)) {
            palabras.push_back(palabra);
        }
        archivo.close();
    }
    else {
        cerr << "No se pudo abrir el archivo." << endl;
    }

    return palabras;
}
bool comparacionManual(const string& a, const string& b, const map<char, int>& mapa) {
    size_t minLength = min(a.size(), b.size());
    for (size_t i = 0; i < minLength; ++i) {
        if (mapa.at(a[i]) != mapa.at(b[i])) {
            return mapa.at(a[i]) > mapa.at(b[i]);
        } 
    }
    return a.size() > b.size();
}

int main() {
    // Establecer la localización en español 
    locale loc("es_ES");

    // Nombre del archivo
    string nombreArchivo = "C:/Users/Arnoldmsr/source/repos/tp324_2024-2/obj6/palabras.txt";

    // Leer las palabras del archivo
    vector<string> palabras = leerArchivo(nombreArchivo);

    // Ordenar las palabras de Z a A
    sort(palabras.begin(), palabras.end(), greater<string>());

    // Imprimir las palabras ordenadas
    cout << "Palabras ordenadas de Z a A:" << endl;
    for (const string& palabra : palabras) {
        cout << palabra << endl;
    }

    return 0;
}
