#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <locale>

using namespace std;

// Mapa para manejar caracteres acentuados y especiales sin cambiar 'ñ'
static unordered_map<char, char> mapaAcentos = {
    {'á', 'a'}, {'Á', 'a'}, {'é', 'e'}, {'É', 'e'},
    {'í', 'i'},{'Í', 'i'}, {'ó', 'o'}, {'Ó', 'o'},
    {'ú', 'u'}, {'ü', 'u'},{'Ú', 'u'}, {'Ü', 'u'}
};

// Función para convertir una palabra en minúsculas
string minusculas(const string& palabra) {
    string resultado;
    for (char c : palabra) {
        if (mapaAcentos.find(c) != mapaAcentos.end()) {
            resultado += mapaAcentos.at(c);
        } else {
            
            resultado += tolower(static_cast<unsigned char>(c));
        }
    }
    return resultado;
}

// Función de comparación para ordenar según el alfabeto español
bool compareCastellano(const string& strA, const string& strB) {
    string orden = "abcdefghijklmnñopqrstuvwxyz";
    unordered_map<char, int> mapaOrden;
    for (size_t i = 0; i < orden.size(); ++i) {
        mapaOrden[orden[i]] = i;
    }

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
void compararTodasLasPalabras(const vector<pair<string, string>>& palabras) {
    for (size_t i = 0; i < palabras.size(); ++i) {
        for (size_t j = i + 1; j < palabras.size(); ++j) {
            compareCastellano(palabras[i].second, palabras[j].second);
        }
    }
}

int main() {
    ifstream archivo("C:\\Users\\Arnoldmsr\\projects\\TP20242\\palabras.txt");
    if (!archivo) {
        cerr << "Error al abrir el archivo" << endl;
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

    // Comparar todas las palabras en minúsculas
    compararTodasLasPalabras(palabras);

    return 0;
}