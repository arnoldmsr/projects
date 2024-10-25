#include <iostream>         // Biblioteca para entrada y salida estándar
#include <fstream>          // Biblioteca para operaciones de archivos
#include <vector>           // Biblioteca para utilizar el contenedor vector
#include <string>           // Biblioteca para utilizar el contenedor string
#include <unordered_map>    // Incluir la biblioteca unordered_map

using namespace std;

// Mapa para normalizar caracteres acentuados sin tocar la 'ñ' y 'Ñ'
static unordered_map<char, char> mapaAcentos = {
    {'á', 'a'}, {'Á', 'a'}, {'é', 'e'}, {'É', 'e'},
    {'í', 'i'},{'Í', 'i'}, {'ó', 'o'}, {'Ó', 'o'},
    {'ú', 'u'}, {'ü', 'u'},{'Ú', 'u'}, {'Ü', 'u'},
    {'Ñ', 'ñ'}
};

// Función para convertir una palabra en minúsculas
string minusculas(const string& palabra) {
    string resultado;
    for (char c : palabra) {
        if (mapaAcentos.find(c) != mapaAcentos.end()) {
            resultado += mapaAcentos.at(c);
        } else {
           resultado += tolower(c);
        }
    }
    return resultado;
}

// Función de comparación para ordenar según el alfabeto español
//bool compareCastellano(const pair<string, string>& a, const pair<string, string>& b) 
bool compareCastellano(const string& strA, const string& strB){
    string orden = "abcdefghijklmnñopqrstuvwxyz";
    unordered_map<char, int> mapaOrden;
    for (size_t i = 0; i < orden.size(); ++i) {
        mapaOrden[orden[i]] = i;
    }

    //const string& strA = a.second;
    //const string& strB = b.second;

    size_t len = min(strA.size(), strB.size());
    for (size_t i = 0; i < len; ++i) {
        cout << "Comparando " << strA[i] << " con " << strB[i] << " - valores: " << mapaOrden[strA[i]] << " y " << mapaOrden[strB[i]] << endl;
        if (mapaOrden[strA[i]] != mapaOrden[strB[i]]) {
            bool resultado = mapaOrden[strA[i]] > mapaOrden[strB[i]];
            cout << "Resultado de comparación: " << resultado << endl;
            return resultado;
        }
    }
    bool resultadoFinal = strA.size() > strB.size();
    cout << "Resultado final de comparación por tamaño: " << resultadoFinal << endl;
    return resultadoFinal;
}

// Función para iterar y comparar todas las palabras
void compararTodasLasPalabras(vector<pair<string, string>>& palabras) {
    for (size_t i = 0; i < palabras.size(); ++i) {
        for (size_t j = i + 1; j < palabras.size(); ++j) {
            compareCastellano(palabras[i].second , palabras[j].second);
        }
    }
}

int main() {
    string nombreArchivo = "C:\\Users\\Arnoldmsr\\projects\\TP20242\\palabras.txt";
    ifstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "Error al abrir el archivo " << nombreArchivo << endl;
        return 1;
    }

    vector<pair<string, string>> palabras;
    string palabra;

    // Leer las palabras del archivo y almacenarlas en los vectores
    while (getline(archivo, palabra)) {
        string minus = minusculas(palabra);
        palabras.push_back({palabra, minus});
    }

    archivo.close();

    cout << "Lista de palabras minúsculas:" << endl;
    for (const auto& p : palabras){
        cout << p.second << endl;
    }

    // Comparar todas las palabras en minúsculas
    compararTodasLasPalabras(palabras);

    //insertionSort(palabras);

    //cout << "Lista de palabras originales ordenadas de la Z a la A:" << endl;
    //for (const auto& p : palabras) {
        //cout << p.first << endl; // Imprimir solo la palabra original
    //}

    return 0;
}